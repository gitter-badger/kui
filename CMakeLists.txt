cmake_minimum_required (VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 14)

project(tui_lib)
project(tui_test)

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(TUI_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

set(LIB_SOURCES src/box.cpp src/screen.cpp)
set(TEST_SOURCES test/screen.cpp)
set(EXAMPLES examples/sanity.cpp examples/test.cpp)

include_directories(${INCLUDE_DIRS})
add_library(tui_lib ${LIB_SOURCES})
add_executable(tui_test ${TEST_SOURCES})

target_link_libraries(tui_test tui_lib)

foreach(example ${EXAMPLES})
  get_filename_component(example_name ${example} NAME_WE)
  set(example_exe "example_${example_name}")
  message("Compiling example at ${example} as ${example_exe}")
  add_executable(${example_exe} ${example})
  target_link_libraries(${example_exe} tui_lib)
  
endforeach(example)

find_package(GTest)
if(${GTEST_FOUND})
    include_directories(${GTEST_INCLUDE_DIRS})
    target_link_libraries(tui_test ${GTEST_BOTH_LIBRARIES})
endif()
