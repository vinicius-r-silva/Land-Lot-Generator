cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

# Set the project name and version
project(main)

# Enable OpenMP
find_package(OpenMP REQUIRED)
find_package(OpenCV REQUIRED)


set(SRC_DIR parking_spot_cpp/src)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/gui.cpp
    ${SRC_DIR}/poly.cpp
    ${SRC_DIR}/logger.cpp
    ${SRC_DIR}/layout.cpp
    ${SRC_DIR}/rect.cpp
)

# Add the executable target
add_executable(main ${SOURCES})
target_compile_options(main PUBLIC -Wall -Wextra -Wpedantic)

# Link OpenMP to the target
# target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX ${OpenCV_LIBS})
target_include_directories(main PUBLIC  ${CMAKE_SOURCE_DIR})
target_link_libraries(main ${OpenCV_LIBS} OpenMP::OpenMP_CXX)
