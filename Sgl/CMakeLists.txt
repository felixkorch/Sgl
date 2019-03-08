project(Sgl)

set(sources
    libs/Glad/src/glad.c libs/stb_image/stb_image.cpp src/Application.cpp src/IndexBuffer.cpp src/VertexBuffer.cpp src/VertexArray.cpp
    src/Shader.cpp src/Input.cpp src/Log.cpp src/GenericWindow.cpp src/LayerStack.cpp src/Graphics/BatchRenderer.cpp src/Graphics/ForwardRenderer.cpp
    src/Graphics/Material.cpp src/Graphics/Mesh.cpp src/Graphics/Texture.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs/spdlog/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs/Glad/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs/glm>
            
)

target_link_libraries(${PROJECT_NAME} glfw3)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)