

default: main.o
	g++ main.o parser/parser.o datastructure/deptree.o datastructure/filetoken.o -o wake 

main.o:  parser.o
	g++ -c main.cpp -o main.o 

parser.o :deptree.o parser/parser.cpp parser/parser.hpp
	g++ -c parser/parser.cpp -o parser/parser.o

deptree.o : datastructure/deptree.cpp datastructure/deptree.hpp filetoken.o
	g++ -c -o datastructure/deptree.o datastructure/deptree.cpp 

filetoken.o : datastructure/filetoken.cpp datastructure/filetoken.hpp
	g++ -c -o datastructure/filetoken.o datastructure/filetoken.cpp