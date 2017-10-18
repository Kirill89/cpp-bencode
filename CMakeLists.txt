cmake_minimum_required(VERSION 3.8)
project(torrento)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") #  -pthread

#INCLUDE_DIRECTORIES(cpp-bencoding/install/include)
#LINK_DIRECTORIES(cpp-bencoding/install/lib)

add_executable(torrento ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(torrento) #  libbencoding.a
