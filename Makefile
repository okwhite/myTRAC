#----------------------------------------------------------------------
# make file for MyTRAC system
#----------------------------------------------------------------------
# Makefile
# # Revision 1.1  2022/12/05 
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
	$(CPP) $(CFLAGS) $@ src/main.cpp
bin/chains.o: include/chains.h
	$(CPP) $(CFLAGS) $@ src/chains.cpp
bin/forms.o: include/mytypes.h include/forms.h
	$(CPP) $(CFLAGS) $@ src/forms.cpp
bin/stack.o: include/stack.h
	$(CPP) $(CFLAGS) $@ src/stack.cpp
bin/trac.o: include/mytypes.h include/chains.h include/stack.h include/forms.h \
	    include/TRAC.h include/macro.h include/flib.h 
	$(CPP) $(CFLAGS) $@ src/trac.cpp

# EOF : Makefile
