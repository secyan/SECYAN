add_executable(sqlGentest
    sqlGentest.cpp
)

target_compile_options(sqlGentest PRIVATE "-Wall" "-Wextra")
target_link_libraries(sqlGentest 
    PUBLIC secyan
)