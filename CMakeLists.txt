cmake_minimum_required(VERSION 3.10)

project(Handmade_Server)
project(Handmade_Client)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_FILES ${CMAKE_SOURCE_DIR}/src/Background.h 
${CMAKE_SOURCE_DIR}/src/BoxCollider.h
${CMAKE_SOURCE_DIR}/src/Button.h
${CMAKE_SOURCE_DIR}/src/EndState.h
${CMAKE_SOURCE_DIR}/src/Game.h

set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/Background.cpp 
${CMAKE_SOURCE_DIR}/src/BoxCollider.cpp
${CMAKE_SOURCE_DIR}/src/Button.cpp

add_executable(Handmade_Server ${SOURCE_FILES} ${INCLUDE_FILES})
add_executable(Handmade_Client ${SOURCE_FILES} ${INCLUDE_FILES})

target_include_directories(Handmade_Server PRIVATE ${CMAKE_SOURCE_DIR}/src/SDL)
target_include_directories(Handmade_Client PRIVATE ${CMAKE_SOURCE_DIR}/src/SDL)

target_link_libraries(Handmade 
${CMAKE_SOURCE_DIR}/lib/SDL2.lib 
${CMAKE_SOURCE_DIR}/lib/SDL2main.lib 
${CMAKE_SOURCE_DIR}/lib/SDL2_net.lib)





