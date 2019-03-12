project(Sgl)

set(sources
    libs/Glad/src/glad.c libs/stb_image/stb_image.cpp src/Application.cpp src/IndexBuffer.cpp src/VertexBuffer.cpp src/VertexArray.cpp
<<<<<<< HEAD
    src/Shader.cpp src/GenerticInput.cpp src/Log.cpp src/GenericWindow.cpp src/LayerStack.cpp src/Graphics/Renderer2D_Core.cpp src/Graphics/ForwardRenderer.cpp
    src/Graphics/Material.cpp src/Graphics/Mesh.cpp src/Graphics/Texture2D.cpp
=======
    src/Shader.cpp src/GenericInput.cpp src/Log.cpp src/GenericWindow.cpp src/LayerStack.cpp src/Platform/Core/Renderer2DCore.cpp src/Graphics/ForwardRenderer.cpp
    src/Graphics/Material.cpp src/Graphics/Mesh.cpp src/Graphics/Texture.cpp
>>>>>>> c8cc4bdf354d5cf55e8cb5b60f9061f6fc72a9a1
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs/spdlog/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs/Glad/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs/glm>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/libs/GLFW/include>
            
)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)