//
//  pentago.h
//  projekt1
//
//  Created by Robert Pelka on 06.01.2018.
//  Copyright © 2018 Robert Pelka. All rights reserved.
//

#ifndef pentago_h
#define pentago_h

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct {
    gint x;
    gint y;
} Coordinate;

GtkWidget *window;
GtkWidget *button[6][6];
GtkWidget *rotatebutton[8];
GtkWidget *startbutton;
GtkWidget *giveupbutton;
char matrix[6][6];
char windowchar;

gboolean refresh(gpointer data);
void lock_buttons(void);
void lock_rotatebuttons(void);
void unlock_buttons(void);
void new_game(void);
void alert(gpointer window, char text[12]);
void CSS(void);
void clicked_button(GtkWidget *widget, Coordinate *c);
void set_colors(void);
void new_game(void);
void rotate_right(GtkWidget *widget, Coordinate *c);
void rotate_left(GtkWidget *widget, Coordinate *c);
void show_error(char *komunikat);

#endif /* pentago_h */


