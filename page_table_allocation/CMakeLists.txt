cmake_minimum_required(VERSION 3.10)
project(PageTable_Parition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

file(GLOB PageTable_Parition_Sources
    "${PROJECT_SOURCE_DIR}/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(PageTable_Parition ${PageTable_Parition_Sources})

target_link_libraries(PageTable_Parition)

