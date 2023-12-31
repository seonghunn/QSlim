cmake_minimum_required(VERSION 3.16)
project(QSlim)

# Release type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# libigl
include(libigl)

# CGAL
find_package(CGAL REQUIRED)

# Enable the target igl::glfw
igl_include(glfw)

# Include folder in ./include
include_directories(${CMAKE_SOURCE_DIR}/include/igl)
include_directories(${CMAKE_SOURCE_DIR}/src)
#include_directories(${CMAKE_SOURCE_DIR}/include)


# Add your project files
file(GLOB SRC_FILES src/*.cpp)

# Previously commented out executable; Uncomment if needed.
# add_executable(${PROJECT_NAME} ${SRC_FILES} src/dataparser.h src/dataparser.cpp src/mesh.cpp src/mesh.h)

# Your current executable
add_executable(${PROJECT_NAME} ${SRC_FILES} src/quadratic.h src/helper.h src/manifold.h include/AABB.cpp src/tree.h src/MeshSimplify.h src/self_intersect.h include/tri_tri_intersect.h)

# Linking both igl::glfw and CGAL to your project
target_link_libraries(${PROJECT_NAME} PUBLIC igl::glfw CGAL::CGAL)

