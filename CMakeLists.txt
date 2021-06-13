cmake_minimum_required(VERSION 3.16.3)
project(obj C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -O0 -g3")

find_package(Curses REQUIRED)
include_directories(
        ${CURSES_INCLUDE_DIR}
)

# Create libraries
add_subdirectory(src)

####################################
# Create "rage_app" library
####################################

add_executable(rage_app main.c)
target_link_libraries(rage_app
    PRIVATE
        api_lib
        win_lib
        obj_parser_lib
        projection_lib
        ${CURSES_LIBRARIES}
        ${PANEL_LIBRARIES}
        m
)
