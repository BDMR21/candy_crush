cmake_minimum_required(VERSION 3.20)
project(CandyCrush)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Werror")

add_executable(CandyCrush main.cpp Candy.cpp Cell.cpp controller.cpp model.cpp Square.cpp view.cpp Canvas.cpp)
#add_executable(CandyCrush Image_Candy.cpp)

set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR}/cmake-bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS} ${FLTK_LIBRARIES})