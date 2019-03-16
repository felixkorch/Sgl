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

get_filename_component(DIR_PARENT ../ ABSOLUTE)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${DIR_PARENT}/include>
            $<BUILD_INTERFACE:${DIR_PARENT}/deps/spdlog/include>
            $<BUILD_INTERFACE:${DIR_PARENT}/deps/glm>
            $<BUILD_INTERFACE:${DIR_PARENT}/deps>
            
)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Glad stb_image)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)
