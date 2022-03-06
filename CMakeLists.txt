cmake_minimum_required(VERSION 2.8)
project( cvexample )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( cvexample
    cvexample.cpp
    ColorFilter.cpp
    ReadAVI.cpp
)

target_link_libraries( cvexample ${OpenCV_LIBS} )