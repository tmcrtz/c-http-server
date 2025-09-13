#include "../../include/server.h"

#if _WIN32
// todo: windows implementation


int main(void)
{
	printf("Hello Teto\n");
}


#elif defined(__linux__) || defined(__APPLE__)
// todo: posix implementation


int main(void)
{
	printf("Hello Teto\n");
}


#endif