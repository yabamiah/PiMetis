cmake_minimum_required(VERSION 3.10)
project(PiMetisEyes)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(PiMetisEyes main2.cpp pi_metis_eyes.cpp)

target_link_libraries(PiMetisEyes ${OpenCV_LIBS})
