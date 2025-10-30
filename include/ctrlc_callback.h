#ifndef CTRLC_CALLBACK_H
#define CTRLC_CALLBACK_H

#if _WIN32
BOOL WINAPI CtrlHandler(DWORD ctrlType);

#elif defined(__linux__) || defined(__APPLE__)
void CtrlHandler(int key);
#endif

#endif
