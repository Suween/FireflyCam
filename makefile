#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++
# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
#
# INCLUDES = -I/home/newhall/include  -I../include
INCLUDES = -I/home/vincentc/Documents/FireFlyCamera/libraw1394 -I/home/vincentc/Documents/FireFlyCamera/dc1394 -I/usr/local/include/opencv2 -I/home/vincentc/Documents/FireFlyCamera

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib
 LFLAGS = -L/home/vincentc/Documents/FireFlyCamera/libraw1394 -L/home/vincentc/Documents/FireFlyCamera/dc1394 -L/usr/local/lib
# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm
LIBS = -lraw1394 -ldc1394 -lopencv_core -lopencv_highgui

# define the C source files
#SRCS = FFC.c definitions.c camera.c
SRCS = $(wildcard *.c)

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file 
PROJECT_NAME = Fireflycam

BUILDDIR = .dep

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean run

all:    $(BUILDDIR) $(PROJECT_NAME) 
		@echo
		@echo  "Compilation done for \"$(PROJECT_NAME)\""

run:
	./$(PROJECT_NAME)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(PROJECT_NAME): $(patsubst %,$(BUILDDIR)/%,$(OBJS))
		$(CC) $(BUILDDIR)/*.o $(CFLAGS) $(LIBS) $(INCLUDES) -o $@

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
$(BUILDDIR)/%.o: %.c |$(BUILDDIR)
		$(CC) -c $(CFLAGS) $(INCLUDES) $(LIBS) $< -o $@

clean:
		$(RM) -r $(BUILDDIR)
		$(RM) $(PROJECT_NAME)

depend: $(SRCS)
		makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
