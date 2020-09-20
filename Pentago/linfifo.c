//
//  linfifo.c
//  projekt1
//
//  Created by Robert Pelka on 06.01.2018.
//  Copyright © 2018 Robert Pelka. All rights reserved.
//

#include "linfifo.h"
#include "pentago.h"
#include "gamestatus.h"

void push_text() {
    unlock=0;
    char text[38];
    int counter=1;
    
    text[37]=giveup;
    if(player=='1')
        text[0]='2';
    else if(player=='2')
        text[0]='1';
    for(int i=0; i<6; i++) {
        for(int j=0; j<6; j++) {
            text[counter]=matrix[i][j];
            counter++;
        }
    }
    sendStringToPipe(potoki, text);
}

void get_text() {
    char tmp[38];
    int counter=1;
    
    if(getStringFromPipe(potoki,tmp,39)) {
        gtk_widget_set_sensitive(startbutton, FALSE);
        gtk_widget_set_name(startbutton, "additional");
        unlock++;
        player=tmp[0];
        for(int i=0; i<6; i++) {
            for(int j=0; j<6; j++) {
                matrix[i][j]=tmp[counter];
                counter++;
            }
        }
        if(tmp[37]=='1') {
            unlock--;  
            maybe_restart();         
        }
        if(tmp[37]=='2') {
            unlock--;     
            new_game();        
        }
        if(unlock>1)
            unlock_buttons();
    }
}

void quit() {
    closePipes(potoki);
    gtk_main_quit();
}

void closePipes(PipesPtr pipes) {
    fclose(pipes->fifo_in);
    fclose(pipes->fifo_out);
    free(pipes);
}

PipesPtr initPipes(int argc,char *argv[]) {
    mkfifo("AtoB", 0664);
    mkfifo("BtoA", 0664);
    if(argc<2 || (argv[1][0]!='A' && argv[1][0]!='B') || argv[1][1]!='\0') {
        fprintf(stderr, "\nPentago should be called with one argument: A or B\n\n");
        return NULL;
    }
    PipesPtr pipes=(PipesPtr)malloc(sizeof(struct pipes));
    if(pipes==NULL) {
        fprintf(stderr, "Memory allocation error\n");
    }
    else {
        pipes->isA=(argv[1][0]=='A');
        pipes->fifo_out=openOutPipe(pipes->isA ? "AtoB" : "BtoA");
        pipes->fifo_in=openInPipe(pipes->isA ? "BtoA" : "AtoB");
    }
    return pipes;
}

FILE *openOutPipe(char *name) {
    FILE *pipe=fopen(name, "w+");
    if(pipe==NULL) {
        show_error("Error in creating output pipe");
        exit(-1);
    }
    return pipe;
}

FILE *openInPipe(char *name) {
    FILE *pipe=fopen(name, "r+");
    if(pipe==NULL) {
        show_error("Error in creating input pipe");
        exit(-1);
    }
    int flags, fd;
    fd=fileno(pipe);
    flags=fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return pipe;
}

void sendStringToPipe(PipesPtr pipes, const char *data) {
    int result=fprintf(pipes->fifo_out,"%s",data);
    fflush(pipes->fifo_out);
    if(result==0)
        show_error("Failed to send data");
}

bool getStringFromPipe(PipesPtr pipes, char *buffer, int size) {
    char *result=fgets(buffer,size,pipes->fifo_in);
    fflush(pipes->fifo_in);
    return result!=NULL;
}

