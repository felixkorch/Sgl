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
    include/Sgl.h
    include/Sgl/Input.h
    include/Sgl/Common.h
    include/Sgl/OpenGL.h
    include/Sgl/VertexBufferLayout.h
    include/Sgl/Log.h
    include/Sgl/Window.h
    include/Sgl/EntryPoint.h
    include/Sgl/Application.h
    include/Sgl/Layer.h
    include/Sgl/Log.h
    include/Sgl/GLTypes.h
    include/Sgl/Shader.h
    include/Sgl/Events/EventQueue.h
    include/Sgl/Events/Event.h
    include/Sgl/Events/KeyEvent.h
    include/Sgl/Events/MouseEvent.h
    include/Sgl/Events/ApplicationEvent.h
    include/Sgl/Events/JoystickEvent.h
    include/Sgl/Events/KeyCodes.h
    include/Sgl/LayerStack.h
    include/Sgl/IndexBuffer.h
    include/Sgl/VertexBuffer.h
    include/Sgl/VertexArray.h
    include/Sgl/GenericInput.h
    include/Sgl/GenericWindow.h
    include/Sgl/Platform/Core/Renderer2D_Core.h
    include/Sgl/Graphics/ForwardRenderer.h
    include/Sgl/Graphics/Material.h
    include/Sgl/Graphics/Mesh.h
    include/Sgl/Graphics/Texture2D.h
    include/Sgl/Graphics/Renderable2D.h
    include/Sgl/Graphics/Renderer2D.h
    include/Sgl/Graphics/Model.h
    include/Sgl/Graphics/Light.h
    include/Sgl/Graphics/Camera.h
    include/Sgl/Graphics/Camera2D.h
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
