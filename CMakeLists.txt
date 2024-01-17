cmake_minimum_required (VERSION 3.25)

project(genpass
        LANGUAGES CXX
        VERSION 0.2.1
        DESCRIPTION "Password generator")
        
set(PROJECT_AUTHOR crow16384)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_NAME GenPassLib)
set(TARGET_NAME genpass)

add_subdirectory(configured)
add_subdirectory(src)
add_subdirectory(app)

include_directories(${LIB_HEADERS})

set(Boost_USE_STATIC_LIBS ON)  # only find static libs

# Boost
find_package(Boost COMPONENTS program_options REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${TARGET_NAME} PUBLIC ${LIB_NAME} ${Boost_LIBRARIES})
endif()
