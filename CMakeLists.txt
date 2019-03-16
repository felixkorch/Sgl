project(Sgl)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

if(!MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

add_subdirectory(deps/GLFW)
add_subdirectory(deps/Glad)
add_subdirectory(deps/stb_image)

set(sources
    src/Application.cpp
    src/Layer.cpp
    src/Log.cpp
    src/Shader.cpp
    src/EventQueue.cpp
    src/LayerStack.cpp
    src/IndexBuffer.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/GenericInput.cpp
    src/GenericWindow.cpp
    src/Platform/Core/Renderer2D_Core.cpp
    src/Graphics/ForwardRenderer.cpp
    src/Graphics/Material.cpp
    src/Graphics/Mesh.cpp
    src/Graphics/Texture2D.cpp
)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/spdlog/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/glm>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps>
            
)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Glad stb_image)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)

add_subdirectory(test)
