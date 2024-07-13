cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 20)

FIND_FILE(SFML_CMAKE_DIR "cmake/Modules/FindSFML.cmake")

# set the project name
project(Iliade VERSION 0.0.2)


include_directories(SYSTEM include)
include_directories(SYSTEM ../shared/include)
include_directories(SYSTEM ../shared/include/external)

find_package(SFML 2.5 
  COMPONENTS 
    system window graphics network audio REQUIRED)

find_package(box2d REQUIRED)

file(GLOB_RECURSE allfiles
     "src/*.cpp"
     "../shared/src/*.cpp"
)

# add the executable
add_executable(iliade-core ${allfiles})

target_include_directories(iliade-core 
  PRIVATE "${PROJECT_BINARY_DIR}")

target_link_libraries(iliade-core sfml-graphics)
target_link_libraries(iliade-core box2d)
