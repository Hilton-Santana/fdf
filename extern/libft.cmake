if (TARGET libft)
    return()
endif()


include(FetchContent)

FetchContent_Declare(
    libft
    GIT_REPOSITORY https://github.com/Hilton-Santana/libft.git
    GIT_TAG        v1.0.0
)

FetchContent_MakeAvailable(libft)

