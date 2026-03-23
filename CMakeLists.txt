cmake_minimum_required(VERSION 3.10)
project(autonomous-sensor-pipeline)

include_directories(include)

add_library(sensor lib/sensor.cpp)
add_library(processor lib/processor.cpp)
add_library(logger lib/logger.cpp)

add_executable(main src/main.cpp)

target_link_libraries(main sensor processor logger)