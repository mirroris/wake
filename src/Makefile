

default:  parser/parser.o datastructure/deptree.o
	g++ main.o parser/parser.o datastructure/deptree.o -o wake 

%.o : %.cpp
	g++ -c $< -o $@  