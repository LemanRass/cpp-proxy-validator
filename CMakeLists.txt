# CMakeList.txt : CMake project for cpp-proxy-validator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("cpp-proxy-validator")

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable (cpp-proxy-validator 
"cpp-proxy-validator.cpp" "cpp-proxy-validator.h" 
"Logger.h" "Logger.cpp"
"ProxyList.h" "ProxyList.cpp")

# TODO: Add tests and install targets if needed.

find_package(CURL CONFIG REQUIRED)
target_link_libraries(cpp-proxy-validator PRIVATE CURL::libcurl)