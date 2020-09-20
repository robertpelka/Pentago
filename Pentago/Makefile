CC=gcc
CFLAGS = -std=c99 -Wall -Werror
LFLAGS = -lm 
GTKFLAGS = `pkg-config gtk+-3.0 --cflags --libs`

NAME = pentago
SRC = main.c pentago.c gamestatus.c linfifo.c
DEPS = pentago.h gamestatus.h linfifo.h
$(NAME): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(GTKFLAGS)

clean:
	rm -f $(NAME)

