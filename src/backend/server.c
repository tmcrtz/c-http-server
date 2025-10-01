#include "../../include/server.h"
#define IP_ADDRESS "127.0.0.1"

#if _WIN32
// TODO: windows implementation


int main(void)
{
	// TODO: Write stuff.	
}


#elif defined(__linux__) || defined(__APPLE__) || defined(_WIN32) 
// remove defined(_WIN32) before prod, but for now keep it so the lsp works on windows.
// TODO: posix implementation


int main(void)
{

	struct addrinfo hints = 
	{
		.ai_family 		= AF_INET,     //Allow IPv4
		.ai_socktype 	= SOCK_STREAM, //TCP socket type
		.ai_protocol	= IPPROTO_TCP, //TCP protocol
		.ai_flags 		= 0,           //no wildcard
	};

	struct addrinfo* result;


	int error_code = getaddrinfo(
		IP_ADDRESS, 
		NULL, 
		&hints, 
		&result);

	if (error_code == -1)
	{
		printf("An error has occured with getaddrinfo(). Error: %s\n", strerror(error_code);
		exit(-1);
	}


	return 0;
}


#endif
