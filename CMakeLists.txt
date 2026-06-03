cmake_minimum_required(VERSION 3.16)
project(PhysicsEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)

set(SFML_DIR "/opt/homebrew/lib/cmake/SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(PhysicsEngine ${SOURCES})

target_include_directories(PhysicsEngine PRIVATE src)
target_link_libraries(PhysicsEngine PRIVATE SFML::Graphics SFML::Window SFML::System)

if(APPLE)
    set_target_properties(PhysicsEngine PROPERTIES
        BUILD_RPATH "/opt/homebrew/lib"
    )
endif()
