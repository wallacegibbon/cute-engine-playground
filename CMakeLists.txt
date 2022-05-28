cmake_minimum_required(VERSION 3.16.0)
set(PRJ_NAME cute-engine-playground)
project(${PRJ_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cute-engine)

aux_source_directory(./src SRCS)
add_executable(${PRJ_NAME} ${SRCS})

target_link_libraries(${PRJ_NAME} PRIVATE CuteEngine)
