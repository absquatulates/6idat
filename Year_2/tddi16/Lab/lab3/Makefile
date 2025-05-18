#
# Makefile för wordchain
#
CCC      := g++
CCFLAGS  := -std=c++17 -pedantic -Wall -g
OPT		 := -O3
EXEC	 := first second

all: clean $(EXEC)


first:
	$(CCC) wordchain.cpp -o first $(CCFLAGS) $(OPT)

second:
	$(CCC) wordchain2.cpp -o second $(CCFLAGS) $(OPT)

clean:
	@ \rm -f $(EXEC) *~
