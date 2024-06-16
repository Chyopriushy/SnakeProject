CC = g++

LDLIBS = -lncursesw
OBJS = main.o coordinate.o item.o snake.o map.o game.o

TARGET = SnakeGameExe

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

coordinate.o : coordinate.cpp coordinate.h
	$(CC) -c coordinate.cpp

item.o : item.cpp item.h coordinate.h map.h
	$(CC) -c item.cpp

map.o : map.cpp map.h coordinate.h
	$(CC) -c map.cpp

snake.o : snake.cpp snake.h coordinate.h
	$(CC) -c snake.cpp

game.o : game.cpp game.h map.h snake.h item.h
	$(CC) -c game.cpp

main.o : main.cpp game.h
	$(CC) -c main.cpp

clean :
	rm -rf $(TARGET) $(OBJS)
run :
	./$(TARGET)
