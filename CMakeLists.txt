project(chess)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER /home/wyxm/EmbeddedSystems/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /home/wyxm/EmbeddedSystems/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++)

set(CMAKE_C_FLAGS "-Wall -O2")
set(CMAKE_EXE_LINKER_FLAGS "-Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
include_directories(.)
include_directories(common/external/include)
link_directories(common/external/lib)
add_subdirectory(common)
add_subdirectory(src)
add_executable(chess main.cpp)
target_link_libraries(chess chess_lib)