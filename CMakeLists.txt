cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(coun LANGUAGES C)
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 23)

add_executable(${PROJECT_NAME} src/main.c src/arg.c src/coun.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

include(CTest)
enable_testing()

add_executable(test_arg test/test_arg.c src/arg.c)
target_include_directories(test_arg PUBLIC include)

add_test(NAME Args1 COMMAND test_arg "")
add_test(NAME Args2 COMMAND test_arg "-h")
add_test(NAME Args3 COMMAND test_arg "--help")
add_test(NAME Args4 COMMAND test_arg "-bcwlh")
