execute_process(
  COMMAND bison --header=Parser.h -o Parser.cpp rvlang.yy
  COMMAND flex -d --header-file=Lexer.h -o Lexer.cpp rvlang.ll
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/parser
  OUTPUT_VARIABLE output
  RESULTS_VARIABLE results
  ERROR_VARIABLE error)
# COMMAND_ERROR_IS_FATAL ANY
if(NOT "${results}" EQUAL "0;0")
  message(STATUS "output: ${output}")
  message(STATUS "result: ${results}")
  message(FATAL_ERROR "error: ${error}")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_sources(compiler PUBLIC CompilerInstance.cpp Ast.cpp Token.cpp Sema.cpp IREmiter.cpp
                               parser/Parser.cpp parser/Lexer.cpp)
