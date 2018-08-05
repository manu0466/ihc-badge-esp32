cmake_minimum_required (VERSION 2.6)
project (wifi_app)

include_directories(
    include
    ../ui/include
    ../hwcontext/include
)

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -ggdb")
endif()

set(SNAKE_APP_SOURCES
        wifi_app.c
)

add_library(wifi_app ${SNAKE_APP_SOURCES})
set_property(TARGET wifi_app PROPERTY C_STANDARD 99)
