cmake_minimum_required(VERSION 3.23)
project(fdf C)


# Add dependencies
include(extern/dependencies.cmake)


add_executable(fdf src/cam.c
                   src/colors.c
                   src/errors.c
                   src/main.c
                   src/parser_map.c
                   src/raster.c
                   src/render.c
                   src/transformations.c)

target_link_libraries(fdf PRIVATE libft
                                  mlx42)