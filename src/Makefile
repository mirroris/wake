CC=g++
OPT=-O2
COMMAND=wake
MAIN=main
SRC=../bin/./animation/animation.cpp.o ../bin/./animation/face.cpp.o ../bin/./animation/zzz.cpp.o ../bin/./builder/builder.cpp.o ../bin/./datastructure/deptree.cpp.o ../bin/./datastructure/filetoken.cpp.o ../bin/./main.cpp.o ../bin/./parser/parser.cpp.o 
default : $(MAIN)
	$(CC) $(OPT) $(SRC) -o ../bin/$(COMMAND)
animation : ./animation/animation.cpp ./animation/animation.hpp zzz face 
	$(CC) $(OPT) -c ./animation/animation.cpp -o ../bin/animation.o
builder : ./builder/builder.cpp ./builder/builder.hpp 
	$(CC) $(OPT) -c ./builder/builder.cpp -o ../bin/builder.o
deptree : ./datastructure/deptree.cpp ./datastructure/deptree.hpp filetoken 
	$(CC) $(OPT) -c ./datastructure/deptree.cpp -o ../bin/deptree.o
face : ./animation/face.cpp ./animation/face.hpp 
	$(CC) $(OPT) -c ./animation/face.cpp -o ../bin/face.o
filetoken : ./datastructure/filetoken.cpp ./datastructure/filetoken.hpp 
	$(CC) $(OPT) -c ./datastructure/filetoken.cpp -o ../bin/filetoken.o
main : ./main.cpp parser builder 
	$(CC) $(OPT) -c ./main.cpp -o ../bin/main.o
parser : ./parser/parser.cpp ./parser/parser.hpp deptree 
	$(CC) $(OPT) -c ./parser/parser.cpp -o ../bin/parser.o
zzz : ./animation/zzz.cpp ./animation/zzz.hpp 
	$(CC) $(OPT) -c ./animation/zzz.cpp -o ../bin/zzz.o
