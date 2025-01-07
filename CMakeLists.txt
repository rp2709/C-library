cmake_minimum_required(VERSION 3.16)
project(C_Objects)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(utils)

add_subdirectory(allocator)
target_link_libraries(LibAlloc LibUtils)

add_subdirectory(queue)
target_link_libraries(LibQueue LibUtils LibAlloc)

add_subdirectory(dynamic_array)
target_link_libraries(LibDyna LibUtils LibAlloc)

add_subdirectory(string)
target_link_libraries(LibString LibDyna LibUtils)

add_subdirectory(stack)
target_link_libraries(LibStack LibUtils)

add_subdirectory(lists)
target_link_libraries(LibList LibUtils LibAlloc)

add_subdirectory(hash_map)
target_link_libraries(LibHMap LibUtils LibList)