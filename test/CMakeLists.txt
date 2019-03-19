set(SGL_TESTS
	DropTest
	MouseTest
	TextureTest
)

foreach (test ${SGL_TESTS})
        add_executable(${test} ${test}.cpp)

		target_link_libraries(${test} Sgl ${SGL_LIBRARIES})

		set_target_properties(${test} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/${test}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/${test})

endforeach()