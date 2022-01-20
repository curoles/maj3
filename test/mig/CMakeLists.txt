add_library(mig
    ${CMAKE_CURRENT_SOURCE_DIR}/mig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fetch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/decode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/execute.cpp
)

add_executable(mig_test_1 ${CMAKE_CURRENT_SOURCE_DIR}/mig_test_1.cpp)
add_dependencies(mig_test_1 mig)
target_link_libraries(mig_test_1 mig maj3module)

add_test(NAME mig_test_1 COMMAND mig_test_1)
