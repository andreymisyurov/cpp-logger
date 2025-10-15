cmake_minimum_required(VERSION 3.10)
project(cpp-logger)

add_library(Logger STATIC Logger.cpp)

target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Logger PUBLIC spdlog::spdlog)
