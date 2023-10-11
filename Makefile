CC=g++
OPT=-O2
COMMAND=wake
BINDIR=bin
SRC=$(BINDIR)/src/animation/animation.o $(BINDIR)/src/animation/face.o $(BINDIR)/src/animation/zzz.o $(BINDIR)/src/builder/builder.o $(BINDIR)/src/datastructure/deptree.o $(BINDIR)/src/datastructure/filetoken.o $(BINDIR)/src/main.o $(BINDIR)/src/parser/parser.o 
MAIN=$(BINDIR)/src/animation/animation.o $(BINDIR)/src/main.o 
dir_guard=@mkdir -p $(@D)
default : $(MAIN)
	$(dir_guard)
	$(CC) $(OPT) $(SRC) -o $(BINDIR)/$(COMMAND)
$(BINDIR)/src/parser/parser.o : src/parser/parser.cpp src/parser/parser.hpp $(BINDIR)/src/datastructure/deptree.o 
	$(dir_guard)
	$(CC) $(OPT) -c src/parser/parser.cpp -o $@
$(BINDIR)/src/animation/animation.o : src/animation/animation.cpp src/animation/animation.hpp $(BINDIR)/src/animation/zzz.o $(BINDIR)/src/animation/face.o 
	$(dir_guard)
	$(CC) $(OPT) -c src/animation/animation.cpp -o $@
$(BINDIR)/src/animation/face.o : src/animation/face.cpp src/animation/face.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c src/animation/face.cpp -o $@
$(BINDIR)/src/datastructure/filetoken.o : src/datastructure/filetoken.cpp src/datastructure/filetoken.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c src/datastructure/filetoken.cpp -o $@
$(BINDIR)/src/main.o : src/main.cpp $(BINDIR)/src/parser/parser.o $(BINDIR)/src/builder/builder.o 
	$(dir_guard)
	$(CC) $(OPT) -c src/main.cpp -o $@
$(BINDIR)/src/animation/zzz.o : src/animation/zzz.cpp src/animation/zzz.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c src/animation/zzz.cpp -o $@
$(BINDIR)/src/builder/builder.o : src/builder/builder.cpp src/builder/builder.hpp 
	$(dir_guard)
	$(CC) $(OPT) -c src/builder/builder.cpp -o $@
$(BINDIR)/src/datastructure/deptree.o : src/datastructure/deptree.cpp src/datastructure/deptree.hpp $(BINDIR)/src/datastructure/filetoken.o 
	$(dir_guard)
	$(CC) $(OPT) -c src/datastructure/deptree.cpp -o $@
