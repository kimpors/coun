cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(coun LANGUAGES C)
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(C_STANDARD 23)

add_executable(${PROJECT_NAME} src/main.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
