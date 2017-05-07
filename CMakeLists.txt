cmake_minimum_required (VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_LIB kui_lib)
set(PROJECT_TEST kui_test)

project(${PROJECT_LIB})
project(${PROJECT_TEST})

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(KUI_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

set(LIB_SOURCES src/box.cpp src/screen.cpp src/input.cpp)
set(TEST_SOURCES test/logger.cpp test/vector2d.cpp)
set(EXAMPLES examples/sanity.cpp examples/test.cpp)

include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_LIB} ${LIB_SOURCES})
add_executable(${PROJECT_TEST} ${TEST_SOURCES})

target_link_libraries(${PROJECT_TEST} ${PROJECT_LIB})

foreach(example ${EXAMPLES})
  get_filename_component(example_name ${example} NAME_WE)
  set(example_exe "example_${example_name}")
  message("Compiling example at ${example} as ${example_exe}")
  
  add_executable(${example_exe} ${example})
  target_link_libraries(${example_exe} ${PROJECT_LIB})
endforeach(example)

find_package(GTest)
if(${GTEST_FOUND})
    include_directories(${GTEST_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_TEST} ${GTEST_BOTH_LIBRARIES})
endif()

enable_testing()
add_test(NAME test COMMAND test)
