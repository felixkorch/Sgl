project(Sgl)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

if(!MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

# Run Conan to make CMake variables available 
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(Sgl_SOURCE
    src/Application.cpp
    src/Layer.cpp
    src/Log.cpp
    src/Shader.cpp
    src/EventQueue.cpp
    src/LayerStack.cpp
    src/IndexBuffer.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/BaseInput.cpp
    src/BaseWindow.cpp
    src/Graphics/Renderer2D.cpp
    src/Graphics/Renderable2D.cpp
    src/Graphics/Texture2D.cpp
    src/Graphics/FrameBuffer2D.cpp
    src/Graphics/Camera2D.cpp
    src/Graphics/Group.cpp
    src/Graphics/stb_image.cpp
    src/ImGui/ImGuiLayer.cpp
    src/ImGui/ImGuiRenderer.cpp
)

list(APPEND Sgl_LIBRARIES Glad ${CONAN_LIBS})

add_library(${PROJECT_NAME} ${Sgl_SOURCE})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
            ${CONAN_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} ${Sgl_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)

if(("${PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}"))
    add_subdirectory(examples)
endif()