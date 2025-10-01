#include "../../include/server.h"
#define IP_ADDRESS "127.0.0.1"

#if _WIN32
// todo: windows implementation


int main(void)
{
	printf("Hello Teto\n");
}


#elif defined(__linux__) || defined(__APPLE__) || defined(_WIN32) 
// remove defined(_WIN32) before prod, but for now keep it so the lsp works on windows.
// todo: posix implementation
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>



int main(void)
{

	struct addrinfo hints = 
	{
		.ai_family 		= AF_INET, //Allow IPv4
		.ai_socktype 	= SOCK_STREAM, //TCP socket type
		.ai_protocol	= IPPROTO_TCP, //TCP protocol
		.ai_flags 		= 0, //no wildcard
	};

	struct addrinfo *result;


	int error_code = getaddrinfo(
		IP_ADDRESS, 
		NULL, 
		&hints, 
		&result);
	printf("%i\n", error_code);


	return 0;
}


#endif
