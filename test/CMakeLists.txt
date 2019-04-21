set(Sgl_TESTS
	# DropTest
	# MouseTest
	TextureTest
)

get_filename_component(PARENT_DIR ../ ABSOLUTE)

foreach (test ${Sgl_TESTS})
        add_executable(${test} ${test}.cpp)

		target_link_libraries(${test} Sgl ${Sgl_LIBRARIES})

		set_target_properties(${test} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PARENT_DIR}/bin/Debug/${test}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PARENT_DIR}/bin/Release/${test})
add_executable(Nemu ../Nemu/src/Main.cpp)
target_link_libraries(Nemu Sgl ${Sgl_LIBRARIES})
target_include_directories(Nemu PRIVATE ../Nemu/include)

endforeach()