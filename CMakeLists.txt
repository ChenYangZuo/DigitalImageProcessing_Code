cmake_minimum_required(VERSION 3.15)
project(DigitalImageProcessing_Code)

set(CMAKE_CXX_STANDARD 11)

add_executable(DigitalImageProcessing_Code main.cpp)

find_package(OpenCV REQUIRED)

target_link_libraries(DigitalImageProcessing_Code ${OpenCV_LIBS})