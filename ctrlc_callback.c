#include <stdio.h>
#include <windows.h>

// Callback function to handle CTRL-C event
BOOL WINAPI CtrlCHandler(DWORD ctrlType)
{
    if (ctrlType == CTRL_C_EVENT)
    {
        printf("\nCTRL-C pressed. Callback function called.\n");
        return TRUE;
    }
    return FALSE;
}
