cmake_minimum_required(VERSION 3.10)
project(http-server)

set(SOURCE_FILE)
	src/backend/server.c
)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Werror -pedantic)
endif()

add_executable(http-server ${SOURCE_FILES})

if (WIN32)
	target_link_libraries(http-server Ws2_32.lib)
endif()
