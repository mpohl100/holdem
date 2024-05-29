find_package(Catch2 REQUIRED)

add_executable(tests tests.cpp ClassifiedHandTests.cpp CardTests.cpp DealerTests.cpp)
target_link_libraries(tests game Catch2::Catch2WithMain)
target_include_directories(tests PUBLIC ../src)
add_test(NAME test COMMAND $<TARGET_FILE:tests>)