cmake_minimum_required(VERSION 2.8)
project(tlsserver)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${ROOT}/bin)
set(CMAKE_CXX_STANDARD 11)

include_directories(
    ${ROOT}/inc
)

# server
file(GLOB_RECURSE SCppFiles ${ROOT}/src/main_s.cpp ${ROOT}/src/server.cpp ${ROOT}/src/client.cpp)
file(GLOB_RECURSE SHppFiles ${ROOT}/src/*.h)

add_executable(tlsserver ${SCppFiles} ${SHppFiles})
target_link_libraries(tlsserver pthread ssl crypto)

# client
file(GLOB_RECURSE CCppFiles ${ROOT}/src/main_c.cpp ${ROOT}/src/client.cpp)
file(GLOB_RECURSE CHppFiles ${ROOT}/src/client.h)

add_executable(tlsclient ${CCppFiles} ${CHppFiles})
target_link_libraries(tlsclient pthread ssl crypto)
