set(LIB_SOURCES 
    "parser.cpp"
    "generator.cpp"
)

set(LIB_HEADERS
    "password.hpp"
    "parser.hpp"
    "generator.hpp"
)

add_library(${LIB_NAME} STATIC
    ${LIB_SOURCES}
    ${LIB_HEADERS}
)
target_include_directories(${LIB_NAME} PUBLIC
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")