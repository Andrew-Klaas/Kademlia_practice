
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_STANDARD 14)


project(Kademlia)
 
#Bring the headers, such as Student.h into the project
include_directories(include)

 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cc")
 
add_executable(testKademlia ${SOURCES})
 
TARGET_LINK_LIBRARIES( testKademlia 
pthread
ssl
crypto
)
