#include "../../include/server.h"
#include <stdio.h>
#include <windows.h>
#include "pause.h"
#include "ctrlc_callback.h"
#define IP_ADDRESS "127.0.0.1"

#define WINDOWS false 
#define POSIX   false

#if WINDOWS
// TODO: windows implementation


int main(void)
{
	// TODO: Write stuff.
	// install CTRL-C handler
    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
        printf("Error: Could not set control handler.\n");
        return 1;
    }

    printf("Server running...\n");

    // use pause from Task 1
    pause_program();
    // second pause after program exits so that the user can see the exit message before the console window closes
    printf("Exiting program.\n");
    pause_program();
    return 0;	
}


#elif POSIX
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
