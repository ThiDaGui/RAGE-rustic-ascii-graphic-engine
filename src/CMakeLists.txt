####################################
# Create "vector3_lib" library
####################################

add_library(vector3_lib STATIC vector3.c)

####################################
# Create "triangle_lib" library
####################################

add_library(triangle_lib STATIC triangle.c)

####################################
# Create "h_triangle_lib" library
####################################

add_library(h_triangle_lib STATIC h_triangle.c)

####################################
# Create "vector4_lib" library
####################################

add_library(vector4_lib STATIC vector4.c)

####################################
# Create "vertex_lib" library
####################################

add_library(vertex_lib STATIC vertex.c)

####################################
# Create "obj_lib" library
####################################

add_library(obj_lib STATIC obj.c)
target_link_libraries(obj_lib
	PRIVATE
		vector3_lib
)

####################################
# Create "obj_parser_lib" library
####################################

add_library(obj_parser_lib STATIC parser.c)
target_link_libraries(obj_parser_lib
		PRIVATE
		vector3_lib
		obj_lib
		)

####################################
# Create "win_lib" library
####################################

add_library(win_lib STATIC win.c)

####################################
# Create "matrix_lib" library
####################################

add_library(matrix_lib STATIC matrix.c)


####################################
# Create "t_matrix_lib" library
####################################

add_library(t_matrix_lib STATIC t_matrix.c)

####################################
# Create "api_lib" library
####################################

add_library(api_lib STATIC api.c)
target_link_libraries(api_lib
		PRIVATE
		vector3_lib
		vector4_lib
		t_matrix_lib
		)

####################################
# Create "rasterizer_lib" library
####################################

add_library(rasterizer_lib STATIC rasterizer.c)
target_link_libraries(rasterizer_lib
	PRIVATE
		vector3_lib
)

####################################
# Create "camera_lib" library
####################################

add_library(camera_lib STATIC camera.c)

####################################
# Create "clipping_lib" library
####################################

add_library(clipping_lib STATIC clipping.c)
target_link_libraries(clipping_lib
	PRIVATE
		vertex_lib
		vector3_lib
		vector4_lib
		h_triangle_lib
		triangle_lib
)

####################################
# Create "projection_lib" library
####################################

add_library(projection_lib STATIC projection.c)
target_link_libraries(projection_lib
	PRIVATE
		obj_parser_lib
		api_lib
		vertex_lib
		vector3_lib
		vector4_lib
		triangle_lib
		h_triangle_lib
		clipping_lib
		rasterizer_lib
		m
)
