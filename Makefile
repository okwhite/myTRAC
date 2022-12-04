#----------------------------------------------------------------------
# make file for MyTRAC system
#----------------------------------------------------------------------
# Makefile
# # Revision 1.0  2022/11/12 
# Initial revision
#
#----------------------------------------------------------------------

CFLAGS = -c -o
HDRS   = include/chains.h include/flib.h include/forms.h include/macro.h include/mytypes.h \
         include/stack.h include/TRAC.h include/version.h 
CPP = g++

OBJ = bin/main.o bin/chains.o bin/forms.o bin/stack.o bin/trac.o
SRC = src/main.cpp src/chains.cpp src/forms.cpp src/stack.cpp src/trac.cpp

all: myTRAC

myTRAC: $(OBJ)
	$(CPP) -o myTRAC $(OBJ)

# DEPENDENCIES

bin/main.o: include/version.h
	$(CPP) $(CFLAGS) bin/main.o src/main.cpp
bin/chains.o: include/chains.h
	$(CPP) $(CFLAGS) bin/chains.o src/chains.cpp
bin/forms.o: include/mytypes.h include/forms.h
	$(CPP) $(CFLAGS) bin/forms.o src/forms.cpp
bin/stack.o: include/stack.h
	$(CPP) $(CFLAGS) bin/stack.o src/stack.cpp
bin/trac.o: include/mytypes.h include/chains.h include/stack.h include/forms.h \
	    include/TRAC.h include/macro.h include/flib.h 
	$(CPP) $(CFLAGS) bin/trac.o src/trac.cpp

# EOF : Makefile
