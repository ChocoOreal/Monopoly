OBJS	= main.o Game.o Player.o Cell.o Command.o
SOURCE	= main.cpp Game.cpp Player.cpp Cell.cpp Command.cpp
HEADER	= Game.h Player.h Cell.h Dice.h
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

Game.o: Game.cpp
	$(CC) $(FLAGS) Game.cpp 

Command.o: Command.cpp
	$(CC) $(FLAGS) Command.cpp 

Player.o: Player.cpp
	$(CC) $(FLAGS) Player.cpp 

Cell.o: Cell.cpp
	$(CC) $(FLAGS) Cell.cpp 

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)