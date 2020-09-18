//
//  gamestatus.c
//  projekt1
//
//  Created by Robert Pelka on 06.01.2018.
//  Copyright © 2018 Robert Pelka. All rights reserved.
//

#include "pentago.h"
#include "linfifo.h"
#include "gamestatus.h"

void start() {
    gtk_widget_set_name(startbutton, "additional");
    player='2';
    unlock_buttons();
    gtk_widget_set_sensitive(startbutton, FALSE);
    push_text();
}

void give_up() {
    gtk_widget_set_sensitive(giveupbutton, FALSE);
    giveup='1';
    push_text();
    giveup='0';
}

void maybe_restart() {
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_YES_NO,
                                    "%s", "Maybe restart?");
    gtk_window_set_title(GTK_WINDOW(dialog), "Message");
    int response=gtk_dialog_run(GTK_DIALOG(dialog));
    if(response==GTK_RESPONSE_YES) {
        giveup='2';
        push_text();
        giveup='0';
        new_game();
    }
    gtk_widget_destroy(dialog);
}

int vertical(int x, int y, char color) {
    int sum=1;
    int i=1;
    while(x+i<6) {
        if(matrix[x+i][y]!=color)
            break;
        sum++;
        i++;
    }
    i=1;
    while(x-i>=0) {
        if(matrix[x-i][y]!=color)
            break;
        sum++;
        i++;
    }
    return sum;
}

int horizontal(int x, int y, char color) {
    int sum=1;
    int i=1;
    while(y+i<6) {
        if(matrix[x][y+i]!=color)
            break;
        sum++;
        i++;
    }
    i=1;
    while(y-i>=0) {
        if(matrix[x][y-i]!=color)
            break;
        sum++;
        i++;
    }
    return sum;
}

int diagonal(int x, int y, char color) {
    int sum1=1;
    int sum2=1;
    int i=1;
    while(x+i<6 && y+i<6) {
        if(matrix[x+i][y+i]!=color)
            break;
        sum1++;
        i++;
    }
    i=1;
    while(x-i>=0 && y-i>=0) {
        if(matrix[x-i][y-i]!=color)
            break;
        sum1++;
        i++;
    }
    i=1;
    while(x+i<6 && y-i>=0) {
        if(matrix[x+i][y-i]!=color)
            break;
        sum2++;
        i++;
    }
    i=1;
    while(x-i>=0 && y+i<6) {
        if(matrix[x-i][y+i]!=color)
            break;
        sum2++;
        i++;
    }
    if(sum1>=sum2)
        return sum1;
    else
        return sum2;
}

int is_draw() {
    int test=0;
    for(int i=0; i<6; i++) {
        for(int j=0; j<6; j++) {
            if(matrix[i][j]=='0') {
                test=1;
                break;
            }
        }
    }
    return test;
}

void is_win() {
    int test=0;
    for(int i=0; i<6; i++) {
        for(int j=0; j<6; j++) {
            if(matrix[i][j]=='1') {
                if(horizontal(i, j, '1')>=5 || vertical(i, j, '1')>=5 || diagonal(i, j, '1')>=5) {
                    test=1;
                    break;
                }
            }
            if(matrix[i][j]=='2') {
                if(horizontal(i, j, '2')>=5 || vertical(i, j, '2')>=5 || diagonal(i, j, '2')>=5) {
                    test=2;
                    break;
                }
            }
        }
    }
    if(test==1) {
        alert(window, "Black wins!");
    }
    else if(test==2) {
        alert(window, "White wins!");
    }
    else if(is_draw()==0) {
        alert(window, "It's a draw!");
    }
}
