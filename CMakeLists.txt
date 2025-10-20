cmake_minimum_required(VERSION 3.10)
project(http-server)

if (WIN32)
	set(SOURCE_FILES
		src/backend/server.c
		src/backend/ctrlc_callback.c
		src/backend/pause.c
	)

else()
	set(SOURCE_FILES
		src/backend/server.c
		src/backend/errors.c
		src/backend/return_code.c
	)
	

endif()


if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Werror -pedantic)
endif()

add_executable(http-server ${SOURCE_FILES})

if (WIN32)
	target_link_libraries(http-server Ws2_32.lib)
endif()
