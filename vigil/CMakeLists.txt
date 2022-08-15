cmake_minimum_required(VERSION 3.10)

project(nsense VERSION 2.0)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
include_directories(./include)

aux_source_directory(./* SRC_FILES)
add_executable(nsense ${SRC_FILES})

message("${SRC_FILES}")
target_link_libraries(nsense
pthread
crypto
ssl
sqlite3
lua5.3
)