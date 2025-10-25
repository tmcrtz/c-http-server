#include "../../include/server.h"

#define IP_ADDRESS "127.0.0.1"
#define PORT "6967"

#if _WIN32
#include "../../include/pause.h"
#include "../../include/ctrlc_callback.h"

// structure to store parsed HTTP request info
typedef struct HttpRequest
{
	char method[8];
	char file[256];
} HttpRequest;

// function to parse HTTP request string
HttpRequest parse_http_request(const char *request_str)
{
	HttpRequest httpRequest;
	memset(&httpRequest, 0, sizeof(HttpRequest));
	sscanf(request_str, "%7s %255s", httpRequest.method, httpRequest.file);
	return httpRequest;
}

int main(void)
{
	WSADATA wsaData;

	// initialize winsock
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("WSAStartup failed: %d\n", result);
		return 1;
	}
	printf("Winsock initialized successfully.\n");

	// set up the addrinfo structure which is passed to the getaddrinfo() function
	struct addrinfo *addrResult = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	int iResult = getaddrinfo(NULL, PORT, &hints, &addrResult);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// create a socket
	SOCKET ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %i\n", WSAGetLastError());
		freeaddrinfo(addrResult);
		WSACleanup();
		return 1;
	}
	printf("Socket created successfully.\n");

	// set up listening socket
	iResult = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("Bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		freeaddrinfo(addrResult);
		WSACleanup();
		return 1;
	}
	printf("Socket bound successfully.\n");

	// listen on socket
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
	printf("Listen failed with error: %d\n", WSAGetLastError());
	closesocket(ListenSocket);
	freeaddrinfo(addrResult);
	WSACleanup();
	return 1;
	}
	printf("Listening for connections...\n");

	// install CTRL-C handler
	if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
	{
		printf("Error: Could not set control handler.\n");
		closesocket(ListenSocket);
		freeaddrinfo(addrResult);
		WSACleanup();
		return 1;
	}
	printf("Server running...\n");

	// accept a client connection
	while (1)
	{
		SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("Accept failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			freeaddrinfo(addrResult);
			WSACleanup();
			return 1;
		}
		printf("Client connected.\n");

		// receive data from client
		char recvbuf[2048];
		int recvbuflen = sizeof(recvbuf);
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			recvbuf[iResult] = '\0'; // null-terminate the received data
			printf("Received %d bytes:\n%s\n", iResult, recvbuf);

			// parse HTTP request
			HttpRequest httpRequest = parse_http_request(recvbuf);
			printf("Parsed HTTP Request - Method: %s, File: %s\n", httpRequest.method, httpRequest.file);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());

		// shutdown and close the client socket
		closesocket(ClientSocket);
		printf("Client disconnected.\n");
	}
	
	// wait for user input before exiting
	pause_program();

	// clean up Winsock resources
	closesocket(ListenSocket);
	freeaddrinfo(addrResult);
	WSACleanup();

	// second pause after program exits so that the user can see the exit message before the console window closes
	printf("Exiting program.\n");
	pause_program();
	return 0;
}

#elif defined(__linux__) || defined(__APPLE__)

int main(void)
{
	setbuf(stdout, NULL);
	struct addrinfo hints;
	memset(
		&hints,
		0,
		sizeof(hints));
	hints.ai_family = AF_INET;		 // Allow IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP socket type
	hints.ai_protocol = IPPROTO_TCP; // TCP protocol
	hints.ai_flags = 0;				 // no wildcard

	struct addrinfo *result;

	int getaddr_error_code = getaddrinfo(
		IP_ADDRESS,
		PORT,
		&hints,
		&result);

	error_print(getaddr_error_code, "getaddrinfo()");

	int sockfd = socket(
		result->ai_family,
		result->ai_socktype,
		result->ai_protocol);

	int enable = 1;
	setsockopt(
		sockfd,
		SOL_SOCKET,
		SO_REUSEADDR,
		&enable,
		sizeof(enable));

	int bind_error_code = bind(
		sockfd,
		result->ai_addr,
		result->ai_addrlen);

	int listen_error_code = listen(
		sockfd,
		128);

	int sock_accept = accept(
		sockfd,
		result->ai_addr,
		&result->ai_addrlen);

	char buf[2056]; // set buffer size

	int byte_count = recv(
		sock_accept,
		buf,
		sizeof(buf) - 1,
		0); // receive size in bytes of info, info put into buffer

	buf[byte_count] = '\0'; // add null terminator to end of buffer

	printf("recv()'d %d bytes of data in buf\n", byte_count);
	printf("BUF: %.*s", byte_count, buf); // <-- give printf() the actual data size

	char message[sizeof(buf)];
	strcpy(message, buf); // buf gets modified from strtok, so saving it to message

	char *command;
	char *file;
	char *saveptr;

	command = strtok_r(
		buf,
		" ",
		&saveptr); // buf is tokenized so no longer useable for general usage

	file = strtok_r(
		NULL,
		" ",
		&saveptr); // may have an issue if file name has a space in it

	printf("COMMAND: %s ", command);
	printf("\nFILE: %s", file);

	char *return_header = return_code(404, file);
	printf("\n%s", return_header);

	error_print(sockfd, "socket()");
	error_print(bind_error_code, "bind()");
	error_print(listen_error_code, "listen()");
	error_print(sock_accept, "accept()");

	error_print(byte_count, "recv()");

	int shutdown_error_code = shutdown(sockfd, SHUT_RDWR);
	int close_error_code = close(sockfd);

	error_print(shutdown_error_code, "shutdown()");
	error_print(close_error_code, "close()");

	freeaddrinfo(result);
	return 0;
}

#endif
