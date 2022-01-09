cmake_minimum_required(VERSION 3.19)

include(cmake/Warnings.cmake)
include(FetchContent)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

find_program(CLANG_FOUND clang)
find_program(CLANGXX_FOUND clang++)

if (CLANG_FOUND AND CLANGXX_FOUND)
  set(CMAKE_C_COMPILER ${CLANG_FOUND})
  set(CMAKE_CXX_COMPILER ${CLANGXX_FOUND})
endif()

find_program(MOLD_FOUND mold)
if (MOLD_FOUND AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(STATUS "[cvrptw] mold path: ${MOLD_FOUND}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --ld-path=${MOLD_FOUND}")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fno-omit-frame-pointer -fsanitize=address")

project(icarus VERSION 0.1 LANGUAGES C CXX)

# add_library({PROJECT_NAME} STATIC)
add_executable(
  ${PROJECT_NAME}_exe
    src/main.cxx
)
