cmake_minimum_required(VERSION 3.0)

project(annotGenSql)

add_library(${PROJECT_NAME} sqlGen.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


set(SQLPARSER_LIB ${PROJECT_SOURCE_DIR}/../../extern/sql-parser/libsqlparser.so)

target_link_libraries(annotGenSql 
                        PUBLIC ${SQLPARSER_LIB})

target_include_directories(${PROJECT_NAME} 
                            PUBLIC ${PROJECT_SOURCE_DIR}/../../extern/sql-parser/src) 
