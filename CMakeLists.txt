cmake_minimum_required (VERSION 3.25)

project(genpass
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "Password generator")

set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME genpass)
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs

# Boost
find_package(Boost COMPONENTS program_options REQUIRED)
if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        add_executable(${TARGET_NAME} main.cpp parser.cpp generator.cpp)
        target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
endif()

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
