cmake_minimum_required(VERSION 3.25)
project(Gravigolf LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp")
add_executable(Gravigolf ${SOURCES})
target_include_directories(Gravigolf PRIVATE include)
target_link_libraries(Gravigolf PRIVATE 
    SFML::Graphics
    SFML::Window
    SFML::System
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
