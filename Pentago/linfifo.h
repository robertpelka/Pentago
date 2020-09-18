//
//  linfifo.h
//  projekt1
//
//  Created by Robert Pelka on 06.01.2018.
//  Copyright © 2018 Robert Pelka. All rights reserved.
//

#ifndef linfifo_h
#define linfifo_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

struct pipes {
    FILE *fifo_in, *fifo_out;
    int isA;
};
typedef struct pipes *PipesPtr;

PipesPtr potoki;
int fileno(FILE *file);
int unlock;

void push_text(void);
void get_text(void);
void quit(void);
void closePipes(PipesPtr pipes);
PipesPtr initPipes(int argc,char *argv[]);
FILE *openOutPipe(char *name);
FILE *openInPipe(char *name);
void sendStringToPipe(PipesPtr pipes, const char *data);
bool getStringFromPipe(PipesPtr pipes, char *buffer, int size);

#endif /* linfifo_h */


