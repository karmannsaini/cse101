#Karmann Saini
#CruzID:2034335
#pa2

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 2
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFindPath       runs FindPath under valgrind on INFILE to OUTFILE
#  make checkClient         runs GraphClient under valgrind
#------------------------------------------------------------------------------


MAIN           = FindPath
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).c
TEST           = GraphClient
TESTOBJ        = $(TEST).o
TESTSRC        = $(TEST).c
ADT1           = Graph
ADT1OBJ        = $(ADT1).o
ADT1SRC        = $(ADT1).c
ADT1_H         = $(ADT1).h
ADT2           = List
ADT2OBJ        = $(ADT2).o
ADT2SRC        = $(ADT2).c
ADT2_H         = $(ADT2).h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
INFILE         = in7
OUTFILE        = myout7


$(MAIN) : $(MAINOBJ) $(ADT1OBJ) $(ADT2OBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADT1OBJ) $(ADT2OBJ)

$(MAINOBJ) : $(MAINSRC) $(ADT1_H)
	$(COMPILE) $(MAINSRC)

$(TEST) : $(TESTOBJ) $(ADT1OBJ) $(ADT2OBJ)
	$(LINK) $(TEST) $(TESTOBJ) $(ADT1OBJ) $(ADT2OBJ)

$(TESTOBJ) : $(TESTSRC) $(ADT1_H) 
	$(COMPILE) $(TESTSRC)

$(ADT1OBJ) : $(ADT1_H) $(ADT2_H) $(ADT1SRC)
	$(COMPILE) $(ADT1SRC)

$(ADT2OBJ) : $(ADT2_H) $(ADT2SRC)
	$(COMPILE) $(ADT2SRC)

clean :
	$(REMOVE) $(MAIN) $(MAINOBJ) $(TEST) $(TESTOBJ) $(ADT1OBJ) $(ADT2OBJ)

check$(MAIN) : $(MAIN)
	$(MEMCHECK) $(MAIN) $(INFILE) $(OUTFILE)

check$(TEST) : $(TEST)
	$(MEMCHECK) $(TEST)