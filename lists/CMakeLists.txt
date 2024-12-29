add_library(LibList
    LinkedList.h
    LinkedList.c
)

add_executable(TEST_LibList main.c)
target_link_libraries(TEST_LibList LibList)