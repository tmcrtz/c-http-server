#include <stdio.h>
#include <windows.h>
#include "pause.h"
#include "ctrlc_callback.h"

int main(void)
{
    // install CTRL-C handler
    if (!SetConsoleCtrlHandler(CtrlCHandler, TRUE))
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
