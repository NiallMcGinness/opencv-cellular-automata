clang++  $(pkg-config --libs --cflags opencv) --std=c++14  -g -o binary.app  main.cpp
