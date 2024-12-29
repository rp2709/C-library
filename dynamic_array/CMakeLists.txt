add_library(LibDyna
    DynamicArray.h
    DynamicArray.c
)

add_executable(TEST_LibDyna main.c)
target_link_libraries(TEST_LibDyna LibDyna)