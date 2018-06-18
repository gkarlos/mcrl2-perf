cmake_minimum_required(VERSION 2.6)

set(PREFIX "mcrl2_perf_benchmark")

set(PROJECT_NAME "${PREFIX}_libatermpp_test")

project( ${PROJECT_NAME} )

add_executable("${PROJECT_NAME}"
  test.cpp
)

target_link_libraries(${PROJECT_NAME}
  mcrl2_atermpp
)
