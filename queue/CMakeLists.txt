add_library(LibQueue
        Circular_Buffer.c
        Circular_Buffer.h
        FIFO.c
        FIFO.h
)

add_executable(TEST_LibQueue main.c)
target_link_libraries(TEST_LibQueue LibQueue)