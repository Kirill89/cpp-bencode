cmake_minimum_required(VERSION 3.8)
project(torrento)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/ByteArray.cpp
        src/Dictionary.cpp
        src/Element.cpp
        src/List.cpp
        src/Number.cpp
        src/TorrentFile.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") #  -pthread

#INCLUDE_DIRECTORIES(cpp-bencoding/install/include)
#LINK_DIRECTORIES(cpp-bencoding/install/lib)

add_executable(torrento main.cpp ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(torrento) #  libbencoding.a

add_executable(torrento_test tests.cpp ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(torrento_test)
