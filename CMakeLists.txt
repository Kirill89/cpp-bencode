cmake_minimum_required(VERSION 3.8)
project(torrento)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/BencodeByteArray.cpp
        src/BencodeDictionary.cpp
        src/BencodeElement.cpp
        src/BencodeList.cpp
        src/BencodeNumber.cpp
        src/TorrentFile.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") #  -pthread

#INCLUDE_DIRECTORIES(cpp-bencoding/install/include)
#LINK_DIRECTORIES(cpp-bencoding/install/lib)

add_executable(torrento main.cpp ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(torrento) #  libbencoding.a

add_executable(torrento_test tests.cpp ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(torrento_test)
