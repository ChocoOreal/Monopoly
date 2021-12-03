OBJS	= main.o Player.o
SOURCE	= main.cpp Player.cpp
HEADER	= Player.h Dice.h
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


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)