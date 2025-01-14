add_library(LibAlloc Allocator.h First_Fit.c
        Standard.c
        allocator.c)

add_executable(TEST_LibAlloc main.c)
target_link_libraries(TEST_LibAlloc LibAlloc)