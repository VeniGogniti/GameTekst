cmake_minimum_required(VERSION 3.28)
project(GameTekst)

execute_process(
        COMMAND wx-config --cxxflags
        OUTPUT_VARIABLE WX_CXXFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND wx-config --libs
        OUTPUT_VARIABLE WX_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WX_CXXFLAGS}")

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED)
include_directories(${wxWidgets_INCLUDE_DIRS})

set(SRC MainWindow.cpp
        Reservation.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SRC})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib ${wxWidgets_LIBRARIES})
