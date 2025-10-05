#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                     makes Words
# make ListClient          makes ListClient
# make clean               removes all binaries
# make checkWords          runs Words under valgrind on INFILE to OUTFILE
# make checkListClient     runs ListClient under valgrind
#------------------------------------------------------------------------------

MAIN           = Words
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).c
TEST           = ListClient
TESTOBJ        = $(TEST).o
TESTSRC        = $(TEST).c
ADT            = List
ADTOBJ         = $(ADT).o
ADTSRC         = $(ADT).c
ADT_H          = $(ADT).h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
INFILE         = in4
OUTFILE        = myout4


$(MAIN) : $(MAINOBJ) $(ADTOBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADTOBJ)

$(MAINOBJ) : $(ADT_H) $(MAINSRC)
	$(COMPILE) $(MAINSRC)

$(TEST) : $(TESTOBJ) $(ADTOBJ)
	$(LINK) $(TEST) $(TESTOBJ) $(ADTOBJ)

$(TESTOBJ) : $(ADT_H) $(TESTSRC)
	$(COMPILE) $(TESTSRC)

$(ADTOBJ) : $(ADT_H) $(ADTSRC)
	$(COMPILE) $(ADTSRC)

clean :
	$(REMOVE) $(MAIN) $(MAINOBJ) $(TEST) $(TESTOBJ) $(ADTOBJ)

check$(MAIN) : $(MAIN)
	$(MEMCHECK) $(MAIN) $(INFILE) $(OUTFILE)

check$(TEST) : $(TEST)
	$(MEMCHECK) $(TEST)