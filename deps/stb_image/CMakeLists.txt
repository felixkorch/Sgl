project(stb_image)

set(sources
    stb_image.cpp
)

get_filename_component(DIR_PARENT ../ ABSOLUTE)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${DIR_PARENT}>
            
)
