#include "../../include/server.h"

#if _WIN32
// todo: windows implementation


int main(void)
{
	printf("Hello Teto\n");
}


#elif defined(__linux__) || defined(__APPLE__) || defined(_WIN32) 
// remove defined(_WIN32) before prod, but for now keep it so the lsp works on windows.
// todo: posix implementation


int main(void)
{
	printf("Hello Teto\n");
}


#endif
