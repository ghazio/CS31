CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable

TARGET = sorter

LIB = readfile.o

SRC = $(TARGET).c

all: $(TARGET)

$(TARGET): $(SRC) $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIB)

$(LIB): readfile.c readfile.h
	$(CC) $(CFLAGS) -c readfile.c

clean:
	$(RM) $(TARGET) $(LIB)
