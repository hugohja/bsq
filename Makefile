# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = bsq

all: $(TARGET)

$(TARGET): bsq.o
	$(CC) $(CFLAGS) -o $(TARGET) bsq.o

bsq.o: bsq.c
	$(CC) $(CFLAGS) -c bsq.c

clean:
	rm -f $(TARGET) *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re

