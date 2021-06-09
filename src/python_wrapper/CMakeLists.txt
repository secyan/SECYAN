set(WRAPPER_NAME python_wrapper)

add_library(${WRAPPER_NAME}
        relation_wrapper.cpp
        )

target_link_libraries(${WRAPPER_NAME}
        PUBLIC secyan
        PUBLIC ENCRYPTO_utils::encrypto_utils
        PUBLIC Boost::program_options)


find_package(pybind11 REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})
message([MAIN] "Found pybind11 v${pybind11_VERSION}: ${pybind11_INCLUDE_DIRS}")

find_package (Python3 COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})
message([MAIN] "Found Python ${PythonLibs_VERSION}: ${Python3_INCLUDE_DIRS}")


pybind11_add_module(${MODULE_NAME} ../core/relation.cpp)
target_compile_definitions(${MODULE_NAME} PRIVATE)

#if (MACOSX)
#    # Solve macOS cannot find ABY error
#    message("Running on MacOS")
#    message("Python3 Library Dirs: ${Python3_LIBRARY_DIRS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include")
#    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${Python3_LIBRARY_DIRS} -lpython3.9")
#
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/Library/Frameworks/Python.framework/Versions/3.8/lib -lpython3.8")
#endif()
#add_executable(loop-conver relation_wrapper.cpp)
#target_link_libraries(loop-conver ${Python3_LIBRARIES})

target_include_directories(${WRAPPER_NAME} PUBLIC ${Python3_INCLUDE_DIRS})
target_include_directories(${WRAPPER_NAME} PUBLIC ${Python3_LIBRARY_DIRS})
