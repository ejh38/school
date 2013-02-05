
#   TARGETS ...: TARGET-PATTERN: DEP-PATTERNS ...
#             COMMANDS
#
# `$<' is the automatic variable that holds the name of the
# prerequisite and `$@' is the automatic variable that holds the name of
# the target; 


# Basic stuff

CC       = gcc 
CFLAGS   = -O3 -Wall 
INC      = -I/usr/X11R6/include  -I/usr/local/include -I/usr/local/include/GL -I/usr/local/lib/include/GL 
LIB      = -L/usr/local/X11/lib64 -L/usr/local/lib/mesa64/lib64/ -lXi -lXmu -lGL -lglut -lGLU  -lm 
PROGRAM  = stitcher
OBJ      = stitcher.o 


$(PROGRAM): $(OBJ) 
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJ)  $(LIB) 

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(PROGRAM)
	/bin/rm -f core
