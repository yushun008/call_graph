cmake_minimum_required(VERSION 3.25)
project(AST_Matcher)

set(CMAKE_BUILD_TYPE Debug)

find_package(Clang REQUIRED CONFIG)
message(STATUS ${Clang_VERSION})
find_package(LLVM REQUIRED CONFIG)
message(STATUS ${LLVM_VERSION})

list(APPEND CMAKE_MODULE_PATH ${Clang_DIR} ${LLVM_DIR})

message(STATUS ${CMAKE_MODULE_PATH})
include_directories("./include")

#添加LLVM cmake配置
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
include(AddLLVM)
#添加clang cmake配置
include_directories(${Clang_INCLUDE_DIRS})
link_directories(${CLANG_LIBRARY_DIRS})
include(AddClang)

set(LLVM_LINK_COMPONETS Support)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_subdirectory(src)
add_clang_executable(main main.cpp)
target_link_libraries(main clangBasic  clangFrontend clangTooling call_graph)
