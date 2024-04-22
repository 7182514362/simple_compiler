#!/bin/bash


bison --header=Parser.h -Wcounterexamples -o Parser.cpp rvlang.yy > 1.txt 2>&1
flex -d --header-file=Lexer.h -o Lexer.cpp rvlang.ll

# bison --header=Parser.h -o Parser.cpp rvlang.yy