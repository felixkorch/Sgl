project(Sandbox)

set(sources
<<<<<<< HEAD
    TextureTest.cpp
=======
    MouseTest.cpp
>>>>>>> c8cc4bdf354d5cf55e8cb5b60f9061f6fc72a9a1
)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${sources})

if(UNIX AND NOT APPLE)
	target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Sgl GL X11 Xrandr Xi Xxf86vm Xinerama Xcursor dl Threads::Threads)
else()
	target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Sgl GL Threads::Threads)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)
