.PHONY   = all clean
CXX      = g++
CXXFLAGS = -ansi -pedantic -Wall -Wno-unused -g
LDFLAGS  = -lSDL -lSDL_image
INCDIR   = ../include
MAINSRC  = main
OBJS     = $(MAINSRC).o ../lib/player.o ../lib/game.o
MAIN     = $(MAINSRC).cpp
EXE      = spaceship

$(EXE): $(MAINSRC).o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@

main.o: $(MAINSRC).cpp
	$(CXX) -I$(INCDIR) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	-$(RM) *.o *~ $(EXE)
