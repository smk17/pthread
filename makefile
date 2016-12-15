OBJ = main.o prodcons.o
TARGET = pthread
CC = gcc
EXT = -lpthread

$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(EXT)

.PHONY : clean
clean :
	-rm $(TARGET) $(OBJ)