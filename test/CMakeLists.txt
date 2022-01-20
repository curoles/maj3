add_executable(test_compilation ${CMAKE_CURRENT_SOURCE_DIR}/test_compilation.cpp)
#add_dependencies(test_compilation some_target)

add_test(NAME test_compilation COMMAND test_compilation)

add_executable(test_adder ${CMAKE_CURRENT_SOURCE_DIR}/test_adder.cpp)
add_test(NAME test_adder COMMAND test_adder)

add_executable(test_dff ${CMAKE_CURRENT_SOURCE_DIR}/test_dff.cpp)
add_test(NAME test_dff COMMAND test_dff)
