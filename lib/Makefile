.PHONY   = all clean
CXX      = g++
CXXFLAGS = -ansi -pedantic -Wall -Wno-unused -g -c
INCDIR   = ../include
OBJS     = player.o game.o

all: $(OBJS)

%.o: %.cpp
	$(CXX) -I$(INCDIR) $(CXXFLAGS) $< -o $@

clean:
	-$(RM) *.o *~
