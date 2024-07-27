TARGET := philosophers
CC := gcc
CFLAGS := -Wall -Wextra #-Werror

INC = includes/
SRC = src/main.c \
	  src/init.c
OBJ = $(SRC:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I $(INC) -o $(TARGET)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I $(INC) $< -c -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all, clean, fclean, re
