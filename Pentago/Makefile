CC=gcc
CFLAGS = -std=c99 -Wall -Werror
LFLAGS = -lm 
GTKFLAGS = `pkg-config gtk+-3.0 --cflags --libs`

NAME = pentago
SRC = main.c pentago.c gamestatus.c linfifo.c
DEPS = pentago.h gamestatus.h linfifo.h
OBJS = main.o pentago.o gamestatus.o linfifo.o

YOU: $(SRC) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS) $(GTKFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(GTKFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(NAME)

