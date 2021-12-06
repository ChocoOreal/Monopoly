OBJS	= main.o Player.o Cell.o
SOURCE	= main.cpp Player.cpp Cell.cpp
HEADER	= Player.h Dice.h Cell.h
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

Player.o: Player.cpp
	$(CC) $(FLAGS) Player.cpp 

Cell.o: Cell.cpp
	$(CC) $(FLAGS)  Cell.cpp
clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)