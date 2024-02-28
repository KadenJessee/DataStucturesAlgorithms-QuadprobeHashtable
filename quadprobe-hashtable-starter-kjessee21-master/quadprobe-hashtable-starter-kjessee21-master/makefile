EXE = bin/HashtableTest
CC = g++
OPTIONS = -std=c++11
DEBUG = -g
MEMCHECK = valgrind --tool=memcheck --leak-check=yes --show-reachable=yes

all:$(EXE)
.PHONY: all run test memcheck clean

run:$(EXE)
	@echo "Press enter to run the test driver"
	@read DUMMY
	@-$(EXE)
	@echo "Press enter to memcheck the test driver"
	@read DUMMY
	$(MEMCHECK) $(EXE)

test: $(EXE)
	$(EXE)

memcheck: $(EXE)
	$(MEMCHECK) $(EXE)

clean:
	mkdir -p obj
	mkdir -p bin
	rm obj/*
	rm bin/*
	rmdir obj
	rmdir bin

$(EXE):obj/HashtableTest.o obj/Hashtable.o
	mkdir -p bin
	$(CC) $(OPTIONS) $(DEBUG) -o $(EXE) obj/HashtableTest.o obj/Hashtable.o

obj/HashtableTest.o:src/HashtableTest.cpp inc/Hashtable.h
	mkdir -p obj
	$(CC) $(OPTIONS) $(DEBUG) -o obj/HashtableTest.o -c  -I inc/ src/HashtableTest.cpp

obj/Hashtable.o:src/Hashtable.cpp inc/Hashtable.h
	mkdir -p obj
	$(CC) $(OPTIONS) $(DEBUG) -o obj/Hashtable.o -c  -I inc/ src/Hashtable.cpp
