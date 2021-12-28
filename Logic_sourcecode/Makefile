OBJS	= Cell.o Command.o CommandHandler.o main.o Player.o RunningGameMode.o Game.o Util.o
SOURCE	= Cell.cpp Command.cpp CommandHandler.cpp main.cpp Player.cpp RunningGameMode.cpp Game.cpp Util.cpp
HEADER	= Dice.h Game.h Cell.h Command.h CommandHandler.h IGame.h Player.h RunningGameMode.h Util.h
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -std=c++17 -o $(OUT) $(LFLAGS)

Cell.o: Cell.cpp
	$(CC) $(FLAGS) Cell.cpp 

Command.o: Command.cpp
	$(CC) $(FLAGS) Command.cpp 

CommandHandler.o: CommandHandler.cpp
	$(CC) $(FLAGS) CommandHandler.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

Player.o: Player.cpp
	$(CC) $(FLAGS) Player.cpp 

RunningGameMode.o: RunningGameMode.cpp
	$(CC) $(FLAGS) RunningGameMode.cpp 

Game.o: Game.cpp
	$(CC) $(FLAGS) Game.cpp 
Util.o: Util.cpp
	$(CC) $(FLAGS) Util.h

clean:
	rm -f $(OBJS) $(OUT)