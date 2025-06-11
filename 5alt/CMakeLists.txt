cmake_minimum_required(VERSION 3.28)

project(7)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_compile_options("-g")

add_executable(out)
target_sources(out
    PUBLIC
    main.cpp
)
target_sources(out
  PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    user.cppm
    i_usr_rep.cppm
    i_data_rep.cppm
    auth_service.cppm
    json_usr_rep.cppm
    json_data_rep.cppm
    i_auth_service.cppm
)
