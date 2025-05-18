# # Makefile
# #

# # Folders
SRC = src

# # this is the directory I will compile from (i.e. the argument to -I)
IDIR := include

# # all object files will be put here
OBJDIR := objdir

# # Compiler (g++)
CCC = g++

# # Compiling flags # #
ifeq ($(shell uname), Darwin)
# MacOS
	CCFLAGS +=  -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -I/opt/homebrew/Cellar/sfml/2.6.1/include
	LDFLAGS += -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio
else
# Linux
	CCFLAGS +=  -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -I$(SFML_ROOT)/include
	LDFLAGS += -L$(SFML_ROOT)/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
endif

# # file which contains the main function
MAINFILE := main.cc

# # Object modules
OBJECTS =  $(OBJDIR)/main.o  $(OBJDIR)/Game.o  $(OBJDIR)/Game_State.o  $(OBJDIR)/Menu_State.o  $(OBJDIR)/Game_Over_State.o $(OBJDIR)/Game_Won_State.o $(OBJDIR)/Entity.o $(OBJDIR)/DynamicEntity.o $(OBJDIR)/Ship.o $(OBJDIR)/Player.o $(OBJDIR)/Cannonball.o $(OBJDIR)/Enemy.o $(OBJDIR)/Obstacle.o $(OBJDIR)/Power_Up.o $(OBJDIR)/Npc.o $(OBJDIR)/Npc_Shooter.o


# # Main objetice - created with 'make main'.
 main: $(OBJECTS) Makefile 
	$(CCC) -I$(IDIR) $(CCFLAGS) -o wos $(OBJECTS) $(LDFLAGS)

# #  Compile and run - created with 'make run'
run: $(OBJECTS) Makefile
	$(CCC) -I$(IDIR) $(CCFLAGS) -o wos $(OBJECTS) $(LDFLAGS)
	./wos


# # Part objectives
 $(OBJDIR)/main.o:  $(SRC)/main.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/main.cc -o $(OBJDIR)/main.o

 $(OBJDIR)/Game.o: $(SRC)/Game.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game.cc -o $(OBJDIR)/Game.o

 $(OBJDIR)/Game_State.o: $(SRC)/Game_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_State.cc -o $(OBJDIR)/Game_State.o

 $(OBJDIR)/Menu_State.o: $(SRC)/Menu_State.cc dir 
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Menu_State.cc -o $(OBJDIR)/Menu_State.o

 $(OBJDIR)/Game_Over_State.o: $(SRC)/Game_Over_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_Over_State.cc -o $(OBJDIR)/Game_Over_State.o

 $(OBJDIR)/Game_Won_State.o: $(SRC)/Game_Won_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_Won_State.cc -o $(OBJDIR)/Game_Won_State.o

 $(OBJDIR)/Entity.o: $(SRC)/Entity.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Entity.cc -o $(OBJDIR)/Entity.o

 $(OBJDIR)/DynamicEntity.o: $(SRC)/DynamicEntity.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/DynamicEntity.cc -o $(OBJDIR)/DynamicEntity.o

 $(OBJDIR)/Ship.o: $(SRC)/Ship.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Ship.cc -o $(OBJDIR)/Ship.o

 $(OBJDIR)/Player.o: $(SRC)/Player.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Player.cc -o $(OBJDIR)/Player.o

 $(OBJDIR)/Cannonball.o: $(SRC)/Cannonball.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Cannonball.cc -o $(OBJDIR)/Cannonball.o

 $(OBJDIR)/Enemy.o: $(SRC)/Enemy.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Enemy.cc -o $(OBJDIR)/Enemy.o
 
 $(OBJDIR)/Obstacle.o: $(SRC)/Obstacle.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Obstacle.cc -o $(OBJDIR)/Obstacle.o

$(OBJDIR)/Power_Up.o: $(SRC)/Power_Up.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Power_Up.cc -o $(OBJDIR)/Power_Up.o

$(OBJDIR)/Npc.o: $(SRC)/Npc.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Npc.cc -o $(OBJDIR)/Npc.o

$(OBJDIR)/Npc_Shooter.o: $(SRC)/Npc_Shooter.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Npc_Shooter.cc -o $(OBJDIR)/Npc_Shooter.o
 dir:
	@mkdir -p $(OBJDIR)

# # 'make clean' removes object files, executables and memory dumps.
 clean:
	@ \rm -rf $(OBJDIR)/*.o *.gch core
	@ \rm -rf wos *~
	@ \rm -rf objdir *~
