project(Sandbox)

set(sources
    src/Sandbox.cpp
)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${sources})

if(UNIX AND NOT APPLE)
	target_link_libraries(${PROJECT_NAME} glfw3 Sgl GL X11 Xrandr Xi Xxf86vm Xinerama Xcursor dl Threads::Threads)
else()
	target_link_libraries(${PROJECT_NAME} glfw3 Sgl GL Threads::Threads)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${PROJECT_NAME}
)