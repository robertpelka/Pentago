//
//  pentago.c
//  projekt1
//
//  Created by Robert Pelka on 06.01.2018.
//  Copyright © 2018 Robert Pelka. All rights reserved.
//

#include "pentago.h"
#include "linfifo.h"
#include "gamestatus.h"

gboolean refresh(gpointer data) {
    get_text();
    set_colors();
    return TRUE;
}

void lock_buttons() {
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            gtk_widget_set_sensitive(button[j][i], FALSE);
    for(int i=0; i<8; i++)
        gtk_widget_set_sensitive(rotatebutton[i], TRUE);
}

void lock_rotatebuttons() {
    for(int i=0; i<8; i++)
        gtk_widget_set_sensitive(rotatebutton[i], FALSE);
}

void unlock_buttons() {
    for(int i=0; i<6; i++) {
        for(int j=0; j<6; j++) {
            if(matrix[j][i]=='0')
                gtk_widget_set_sensitive(button[j][i], TRUE);
        }
    }
    for(int i=0; i<8; i++)
        gtk_widget_set_sensitive(rotatebutton[i], FALSE);
}

void alert(gpointer window, char text[12]) {
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", text);
    gtk_window_set_title(GTK_WINDOW(dialog), "The end of the game");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    new_game();
}

void CSS() {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    const gchar *css_relpath="style.css";
    GError *error=NULL;
    GFile *css_file=g_file_new_for_path(css_relpath);
    
    gtk_css_provider_load_from_file(provider, css_file, &error);
    if(error) {
        g_warning ("%s", error->message);
        g_clear_error (&error);
    }
    g_object_unref(css_file);
}

void clicked_button(GtkWidget *widget, Coordinate *c) {
    if(player=='1') {
        matrix[c->x][c->y]='1';
        gtk_widget_set_name(widget, "button_black");
    }
    else {
        matrix[c->x][c->y]='2';
        gtk_widget_set_name(widget, "button_white");
    }
    push_text();
    lock_buttons();
}

void set_colors() {
    for(int i=0; i<6; i++) {
        for(int j=0; j<6; j++) {
            if(matrix[j][i]=='1')
                gtk_widget_set_name(button[j][i], "button_black");
            else if(matrix[j][i]=='2')
                gtk_widget_set_name(button[j][i], "button_white");
            else
                gtk_widget_set_name(button[j][i], "unpressed");
        }
    }
    is_win();
}

void new_game() {
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            matrix[i][j]='0';
    unlock=-1;
    set_colors();
    lock_buttons();
    lock_rotatebuttons();
    gtk_widget_set_sensitive(startbutton, TRUE);
    gtk_widget_set_name(startbutton, "start");
    gtk_widget_set_sensitive(giveupbutton, TRUE);
}

void rotate_right(GtkWidget *widget, Coordinate *c) {
    int x,y;
    if(c->x==0) {
        x=0;
        y=0;
    }
    else if(c->x==1) {
        x=3;
        y=0;
    }
    else if(c->x==2) {
        x=3;
        y=3;
    }
    else {
        x=0;
        y=3;
    }
    for(int i=0; i<2; i++) {
        char tmp=matrix[y+i][x];
        matrix[y+i][x]=matrix[y+2][x+i];
        matrix[y+2][x+i]=matrix[y+2-i][x+2];
        matrix[y+2-i][x+2]=matrix[y][x+2-i];
        matrix[y][x+2-i]=tmp;
    }
    lock_rotatebuttons();
    push_text();
}

void rotate_left(GtkWidget *widget, Coordinate *c) {
    int x,y;
    if(c->x==4) {
        x=0;
        y=0;
    }
    else if(c->x==5) {
        x=3;
        y=0;
    }
    else if(c->x==6) {
        x=3;
        y=3;
    }
    else {
        x=0;
        y=3;
    }
    for(int i=0; i<2; i++) {
        char tmp=matrix[y][x+2-i];
        matrix[y][x+2-i]=matrix[y+2-i][x+2];
        matrix[y+2-i][x+2]=matrix[y+2][x+i];
        matrix[y+2][x+i]=matrix[y+i][x];
        matrix[y+i][x]=tmp;
    }
    lock_rotatebuttons();
    push_text();
}

void show_error(char *komunikat) {
    GtkWidget *dialog;
    dialog=gtk_message_dialog_new (GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"%s",komunikat);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

