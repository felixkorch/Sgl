set(CMAKE_CXX_STANDARD 14)

set(Sgl_EXAMPLES
	#TextureTest
	#Snake
	ECS
)

get_filename_component(PARENT_DIR ../ ABSOLUTE)

foreach (test ${Sgl_EXAMPLES})
        add_executable(${test} ${test}.cpp)

		target_link_libraries(${test} Sgl ${Sgl_LIBRARIES})

		set_target_properties(${test} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PARENT_DIR}/bin/Debug/${test}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PARENT_DIR}/bin/Release/${test})

endforeach()