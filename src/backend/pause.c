#include "../../include/pause.h"

// Function to pause the program until the user presses Enter
void pause_program(void) 
{
    printf("Press Enter to continue...\n");
    while (getchar() != '\n');
}
