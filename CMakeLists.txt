cmake_minimum_required(VERSION 3.21)
project(ProxyChecker)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProxyChecker main.cpp ProxyList.cpp ProxyList.h Logger.cpp Logger.h)

target_link_libraries(ProxyChecker curl)