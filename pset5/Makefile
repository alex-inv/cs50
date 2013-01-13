#
# Makefile
#
# Computer Science 50
# Problem Set 5
#

# compiler to use
CC = clang
# CC = gcc

# flags to pass compiler
CFLAGS = -ggdb -O3 -Qunused-arguments -std=c99 -Wall -Werror
# CFLAGS = -O3 -Qunused-arguments -std=c99 -Wall -Werror
# CFLAGS = -o3 -std=c99 -Wall -pg

# name for executable
EXE = speller

# space-separated list of header files
HDRS = dictionary.h hasht.h sll.h shared.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = 

# space-separated list of source files
SRCS = speller.c dictionary.c hasht.c sll.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
