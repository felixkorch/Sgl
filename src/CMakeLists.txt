project(Sgl)

set(sources
    Application.cpp
    Layer.cpp
    Log.cpp
    Shader.cpp
    EventQueue.cpp
    LayerStack.cpp
    IndexBuffer.cpp
    VertexBuffer.cpp
    VertexArray.cpp
    GenericInput.cpp
    GenericWindow.cpp
    Platform/Core/Renderer2D_Core.cpp
    Graphics/ForwardRenderer.cpp
    Graphics/Material.cpp
    Graphics/Mesh.cpp
    Graphics/Texture2D.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/deps/spdlog/include>
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/deps/glm>
            
)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Glad stb_image)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)
