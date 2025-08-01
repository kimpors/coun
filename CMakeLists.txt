cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(coun LANGUAGES C VERSION 1.0.0)
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 23)

add_executable(${PROJECT_NAME} src/main.c src/arg.c src/coun.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

include(CTest)
enable_testing()

set(ARG_HELP 1)
set(ARG_FILE 2)
set(ARG_BYTE 4)
set(ARG_CHAR 8)
set(ARG_WORD 16)
set(ARG_LINE 32)
set(ARG_ERROR 64)

add_executable(test_arg test/test_arg.c src/arg.c)
target_include_directories(test_arg PUBLIC include)

math(EXPR ARG1 "${ARG_CHAR} | ${ARG_WORD} | ${ARG_LINE}")
add_test(NAME Args1 COMMAND test_arg ${ARG_ERROR} "")
add_test(NAME Args2 COMMAND test_arg ${ARG_HELP} "-h")
add_test(NAME Args3 COMMAND test_arg ${ARG_HELP} "--help")
add_test(NAME Args4 COMMAND test_arg ${ARG_ERROR} "-bcwlh")

add_executable(test_coun test/test_coun.c src/coun.c)
target_include_directories(test_coun PUBLIC include)

add_test(NAME Coun1 COMMAND test_coun 0 0 0 0 "")
add_test(NAME Coun2 COMMAND test_coun 12 12 2 0 "Hello there!")
add_test(NAME Coun3 COMMAND test_coun 4 2 1 0 " ")
add_test(NAME Coun4 COMMAND test_coun 8 8 4 4 "t\ne\ns\nt\n")
