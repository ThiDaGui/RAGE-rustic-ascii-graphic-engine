cmake_minimum_required(VERSION 3.16.3)
project(RAGE)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -pedantic -Wvla -g")

set(CURSES_NEED_NCURSES 1)
find_package(Curses REQUIRED)
include_directories(
	includes
	${CURSES_INCLUDE_DIR}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Create libraries
add_subdirectory(src)

####################################
# Create "rage_app" library
####################################

add_executable(rage_app main.c)
target_link_libraries(rage_app
	PRIVATE
		api_lib
		camera_lib
		win_lib
		obj_parser_lib
		projection_lib
		${PANEL_LIBRARIES}
		${CURSES_LIBRARIES}
		m
)
# Create documentation
option(BUILD_DOC "Build documentation" OFF)

if(BUILD_DOC)
	# check if Doxygen is installed
	find_package(Doxygen REQUIRED dot)
	if (DOXYGEN_FOUND)
		# use the Doxyfile file to generate the documentation
		add_custom_target(doc
			COMMAND Doxygen::doxygen Doxyfile
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
			COMMENT "Generating API documentation with Doxygen"
			VERBATIM
		)
	else (DOXYGEN_FOUND)
	  message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif(BUILD_DOC)

option(BUILD_TEST"Build tests" OFF)
if (BUILD_TEST)
	include(CTest)
	add_subdirectory(tests)
endif(BUILD_TEST)
