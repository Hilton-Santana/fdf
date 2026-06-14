if (TARGET mlx42)
    return()
endif()


include(FetchContent)

FetchContent_Declare(mlx42
                     GIT_REPOSITORY https://github.com/codam-coding-college/MLX42.git
                     GIT_TAG        v2.0.3)

FetchContent_MakeAvailable(mlx42)