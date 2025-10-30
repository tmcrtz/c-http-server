#include "../../include/server.h"
#if _WIN32
// Callback function to handle CTRL-C event
BOOL WINAPI CtrlHandler(DWORD ctrlType)
{
    switch (ctrlType)
    {
    case CTRL_C_EVENT:
        printf("\nCTRL-C pressed.\n");
        return TRUE;

    case CTRL_CLOSE_EVENT:
        printf("\nConsole window is closing.\n");
        return TRUE;

    case CTRL_BREAK_EVENT:
        printf("\nCTRL-BREAK pressed.\n");
        return TRUE;

    case CTRL_LOGOFF_EVENT:
        printf("\nUser logging off.\n");
        return TRUE;

    case CTRL_SHUTDOWN_EVENT:
        printf("\nSystem shutting down.\n");
        return TRUE;

    default:
        return FALSE;
    }
}

#elif defined(__linux__) || defined(__APPLE__)

void CtrlHandler(int key) 
{
    printf("\nCTRL-C pressed\n");
}

#endif