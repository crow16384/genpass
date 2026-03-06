cmake_minimum_required (VERSION 3.25)

# For clangd: always have compile_commands.json at project root
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(genpass
        LANGUAGES CXX
        VERSION 0.3.0
        DESCRIPTION "Password generator")
        
set(PROJECT_AUTHOR crow16384)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_NAME GenPassLib)
set(TARGET_NAME genpass)

# Default prefix: use -DCMAKE_INSTALL_PREFIX=$HOME/.local for user install
# install(CODE "execute_process(\"strip ${TARGET_NAME}\")")

add_subdirectory(configured)
add_subdirectory(src)
add_subdirectory(app)

include_directories(${LIB_HEADERS})

set(Boost_USE_STATIC_LIBS ON)  # only find static libs

# Boost
find_package(Boost COMPONENTS program_options REQUIRED QUIET)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${TARGET_NAME} PUBLIC ${LIB_NAME} ${Boost_LIBRARIES})
endif()

# Install: binary and man page
install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/man/genpass.1 DESTINATION share/man/man1)

# DEB package (make package or cpack -G DEB)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION "Readable and pronounceable password generator (template-based, supports th/sh/ch digraphs)")
set(CPACK_PACKAGE_VENDOR ${PROJECT_AUTHOR})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${PROJECT_AUTHOR}")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
include(CPack)