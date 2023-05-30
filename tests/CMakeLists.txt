pkg_check_modules(CHECK REQUIRED check)
add_executable(check_clipping check_clipping.c)
target_link_libraries(check_clipping
	PRIVATE
		vector4_lib
		h_triangle_lib
		clipping_lib
		${CHECK_LDFLAGS}
)

add_test(NAME check_clipping COMMAND check_clipping)
