include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(compiler main.cpp Driver.cpp)

add_subdirectory(frontend)
# add_subdirectory(backend)


target_link_libraries(compiler profiler unwind LLVM-14)