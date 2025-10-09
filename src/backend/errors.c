#include "../../include/server.h"

void error_print(int error_code, char* function_name)
{
	if (error_code == -1) 
	{
		printf("An error has occured with %s. Error: %s\n", function_name, strerror(error_code));
		exit(-1);
	}
}