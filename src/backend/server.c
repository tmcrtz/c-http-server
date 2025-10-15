#include "../../include/server.h"

#define IP_ADDRESS "127.0.0.1"
#define PORT "6967"

#if _WIN32
#include "../../include/pause.h"
#include "../../include/ctrlc_callback.h"

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

	error_print(sockfd, "socket()");
	error_print(bind_error_code, "bind()");
	error_print(listen_error_code, "listen()");
	error_print(sock_accept, "accept()");

	int shutdown_error_code = shutdown(sockfd, SHUT_RDWR);
	int close_error_code = close(sockfd);

	error_print(shutdown_error_code, "shutdown()");
	error_print(close_error_code, "close()");

	freeaddrinfo(result);
	return 0;
}

#endif
