cmake_minimum_required (VERSION 2.6)
project (ArithEval)

set (ArithEval_VERSION_MAJOR 1)
set (ArithEval_VERSION_MINOR 0)

set (PROJECT_SOURCE_DIR ./src)

configure_file (
	"${PROJECT_SOURCE_DIR}/arith_eval_config.h.in"
	"${PROJECT_BINARY_DIR}/arith_eval_config.h"
	)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(ArithEval ${PROJECT_SOURCE_DIR}/arith_eval.c)
target_include_directories(ArithEval PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(ArithEval m)
