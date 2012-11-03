CC = arm-linux-gcc

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

TARGET = shell

all: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	cp $(TARGET) ../

clean:
	-rm *.o  $(TARGET)
