add_library(LibHMap
    HashMap.c
    HashMap.h
)

add_executable(TEST_LibHMap main.c)
target_link_libraries(TEST_LibHMap LibHMap)