//
//  gamestatus.h
//  projekt1
//
//  Created by Robert Pelka on 06.01.2018.
//  Copyright © 2018 Robert Pelka. All rights reserved.
//

#ifndef gamestatus_h
#define gamestatus_h

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

char player;
char giveup;

void start(void);
void give_up(void);
void maybe_restart(void);
int vertical(int x, int y, char color);
int horizontal(int x, int y, char color);
int diagonal(int x, int y, char color);
int is_draw(void);
void is_win(void);


#endif /* gamestatus_h */
