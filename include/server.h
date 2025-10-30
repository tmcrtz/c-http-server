#pragma once

#if _WIN32
	// Window API includes
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>

	#include "ctrlc_callback.h"
	#include "pause.h"

#elif defined(__linux__) || defined(__APPLE__)
	// POSIX-compliant API includes
	#include <sys/socket.h>
	#include <pthread.h>
	#include <signal.h>
	#include <netdb.h>
	#include <errno.h>
	#include <unistd.h>
	#include <sys/time.h>
	#include <signal.h>

	#include "errors.h"
	#include "return_code.h"
	#include "ctrlc_callback.h"
	#include "pause.h"

#endif


// C Standard Library or otherwise non-OS specific includes
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


