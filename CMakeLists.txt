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
add_subdirectory(deps/imgui)

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
    src/Graphics/Texture2D.cpp
    src/ImGuiLayer.cpp
    src/ImGuiRenderer.cpp
)

list(APPEND Sgl_LIBRARIES glfw ${GLFW_LIBRARIES} Glad stb_image imgui)

add_library(${PROJECT_NAME} ${Sgl_SOURCE})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/spdlog/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/glm>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/obj_loader/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/imgui>
)

target_link_libraries(${PROJECT_NAME} ${Sgl_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)

if(("${PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}"))
    add_subdirectory(test)
endif()