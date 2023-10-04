CC=g++
OPT=-O2
COMMAND=wake
MAIN=main
BINDIR=../bin
SRCDIR=src
SRC=$(BINDIR)/animation/animation.o $(BINDIR)/animation/face.o $(BINDIR)/animation/zzz.o $(BINDIR)/builder/builder.o $(BINDIR)/datastructure/deptree.o $(BINDIR)/datastructure/filetoken.o $(BINDIR)/main.o $(BINDIR)/parser/parser.o 
dir_guard=@mkdir -p $(@D)
default : $(MAIN)
	$(dir_guard)
	$(CC) $(OPT) $(SRC) -o $(BINDIR)/$(COMMAND)
$(BINDIR)/animation/animation.o : ./animation/animation.cpp ./animation/animation.hpp zzz face 
	$(dir_guard)
	$(CC) $(OPT) -c ./animation/animation.cpp -o $@
$(BINDIR)/builder/builder.o : ./builder/builder.cpp ./builder/builder.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c ./builder/builder.cpp -o $@
$(BINDIR)/datastructure/deptree.o : ./datastructure/deptree.cpp ./datastructure/deptree.hpp filetoken 
	$(dir_guard)
	$(CC) $(OPT) -c ./datastructure/deptree.cpp -o $@
$(BINDIR)/animation/face.o : ./animation/face.cpp ./animation/face.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c ./animation/face.cpp -o $@
$(BINDIR)/datastructure/filetoken.o : ./datastructure/filetoken.cpp ./datastructure/filetoken.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c ./datastructure/filetoken.cpp -o $@
$(BINDIR)/main.o : ./main.cpp parser builder 
	$(dir_guard)
	$(CC) $(OPT) -c ./main.cpp -o $@
$(BINDIR)/parser/parser.o : ./parser/parser.cpp ./parser/parser.hpp deptree 
	$(dir_guard)
	$(CC) $(OPT) -c ./parser/parser.cpp -o $@
$(BINDIR)/animation/zzz.o : ./animation/zzz.cpp ./animation/zzz.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c ./animation/zzz.cpp -o $@
