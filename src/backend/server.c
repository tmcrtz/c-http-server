#include "../../include/server.h"


#define IP_ADDRESS "127.0.0.1"

#if _WIN32 

int main(void)
{
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


#elif defined(__linux__) || defined(__APPLE__) 

int main(void)
{

	struct addrinfo hints;
	memset(
			&hints,
			0,
			sizeof(hints));

	hints->ai_family   = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_protocol = IPPROTO_TCP;
	hints->ai_flags    = 0;

	struct addrinfo* result;


	int error_code = getaddrinfo(
		IP_ADDRESS, 
		NULL, 
		&hints, 
		&result);

	if (error_code == -1)
	{
		printf("An error has occured with getaddrinfo(). Error: %s\n", strerror(error_code));
		exit(-1);
	}


	return 0;
}


#endif
