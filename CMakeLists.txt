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
    # Srcs
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

    # Includes
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Input.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Common.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/OpenGL.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/VertexBufferLayout.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Log.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Window.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/EntryPoint.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Application.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Layer.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Log.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/GLTypes.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Shader.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Events/EventQueue.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Events/Event.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Events/KeyEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Events/MouseEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Events/ApplicationEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Events/JoystickEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Events/KeyCodes.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/LayerStack.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/IndexBuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/VertexBuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/VertexArray.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/GenericInput.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/GenericWindow.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Platform/Core/Renderer2D_Core.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/ForwardRenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Material.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Mesh.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Texture2D.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Renderable2D.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Renderer2D.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Model.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Light.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Camera.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Sgl/Graphics/Camera2D.h
)

list(APPEND SGL_LIBRARIES glfw ${GLFW_LIBRARIES} Glad stb_image)

add_library(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/spdlog/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/glm>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/deps/obj_loader/include>
)

target_link_libraries(${PROJECT_NAME} ${SGL_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)

add_subdirectory(test)
