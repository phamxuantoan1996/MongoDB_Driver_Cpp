cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(app LANGUAGES CXX)
    
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
    
add_executable(app main.cpp)
    
target_link_libraries(app PRIVATE mongo::mongocxx_shared mongo::bsoncxx_shared)