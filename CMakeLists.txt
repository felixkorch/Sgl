cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

if(!MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

include_directories(deps)

add_subdirectory(deps/GLFW)
add_subdirectory(deps/Glad)
add_subdirectory(deps/stb_image)
add_subdirectory(src)
add_subdirectory(test)
