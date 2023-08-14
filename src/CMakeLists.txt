aux_source_directory(. SRC_FILES)
add_clang_library(call_graph SHARED ${SRC_FILES})
target_link_libraries(call_graph clangAST clangSerialization)