cmake_minimum_required(VERSION 3.10)

project(Handmade_Server)
project(Handmade_Client)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_FILES_SERVER ${CMAKE_SOURCE_DIR}/src/Server/ChatServer.h 
${CMAKE_SOURCE_DIR}/src/Server/TCPServer.h
${CMAKE_SOURCE_DIR}/src/Server/TCPSocket.h)

set(SOURCE_FILES_SERVER ${CMAKE_SOURCE_DIR}/src/Server/ChatServer.cpp 
${CMAKE_SOURCE_DIR}/src/Server/Main.cpp
${CMAKE_SOURCE_DIR}/src/Server/TCPServer.cpp
${CMAKE_SOURCE_DIR}/src/Server/TCPSocket.cpp)

set(INCLUDE_FILES_CLIENT ${CMAKE_SOURCE_DIR}/src/Server/ChatClient.h 
${CMAKE_SOURCE_DIR}/src/Server/TCPClient.h
${CMAKE_SOURCE_DIR}/src/Server/TCPSocket.h)

set(SOURCE_FILES_CLIENT ${CMAKE_SOURCE_DIR}/src/Server/ChatClient.cpp 
${CMAKE_SOURCE_DIR}/src/Server/Main.cpp
${CMAKE_SOURCE_DIR}/src/Server/TCPClient.cpp
${CMAKE_SOURCE_DIR}/src/Server/TCPSocket.cpp)

add_executable(Handmade_Server ${SOURCE_FILES_SERVER} ${INCLUDE_FILES_SERVER})
add_executable(Handmade_Client ${SOURCE_FILES_CLIENT} ${INCLUDE_FILES_CLIENT})

target_include_directories(Handmade_Server PRIVATE ${CMAKE_SOURCE_DIR}/src/SDL)
target_include_directories(Handmade_Client PRIVATE ${CMAKE_SOURCE_DIR}/src/SDL)

target_link_libraries(Handmade_Server 
${CMAKE_SOURCE_DIR}/lib/SDL2.lib 
${CMAKE_SOURCE_DIR}/lib/SDL2main.lib 
${CMAKE_SOURCE_DIR}/lib/SDL2_net.lib)

target_link_libraries(Handmade_Client 
${CMAKE_SOURCE_DIR}/lib/SDL2.lib 
${CMAKE_SOURCE_DIR}/lib/SDL2main.lib 
${CMAKE_SOURCE_DIR}/lib/SDL2_net.lib)




