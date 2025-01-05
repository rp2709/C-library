add_library(LibString
    String.c
    String.h
)

add_executable(TEST_LibString main.c)
target_link_libraries(TEST_LibString LibString)