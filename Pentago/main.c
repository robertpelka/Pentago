//
//  main.c
//  projekt1
//
//  Created by Robert Pelka on 06.01.2018.
//  Copyright © 2018 Robert Pelka. All rights reserved.
//

#include "pentago.h"
#include "linfifo.h"
#include "gamestatus.h"

int main(int argc, char *argv[]) {
    if ((potoki=initPipes(argc,argv)) == NULL)
        return 1;
    
    windowchar=argv[1][0];
    unlock=-1;  
    giveup='0';

    GtkWidget *box;
    GtkWidget *grid;
    GtkWidget *grid2;
    gtk_init(&argc, &argv);
    CSS();
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Pentago");
    GdkPixbuf *icon=gdk_pixbuf_new_from_file("images/icon.jpg",NULL);
    gtk_window_set_icon(GTK_WINDOW(window), icon);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    grid=gtk_grid_new();
    grid2=gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid2), TRUE);
    
    for(int i=0; i<8; i++) {
        rotatebutton[i]=gtk_button_new();
        gtk_widget_set_size_request(rotatebutton[i], 45, 45);
    }
    
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[0], 1, 0, 1, 1); //up left
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[4], 0, 1, 1, 1); //up left back
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[7], 1, 7, 1, 1); //down left back
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[3], 0, 6, 1, 1); //down left
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[5], 6, 0, 1, 1); //up right back
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[1], 7, 1, 1, 1); //up right
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[2], 6, 7, 1, 1); //down right
    gtk_grid_attach(GTK_GRID(grid), rotatebutton[6], 7, 6, 1, 1); //down right back
    
    GtkWidget *arrow0=gtk_image_new_from_file("images/arrow0.png");
    GtkWidget *arrow1=gtk_image_new_from_file("images/arrow1.png");
    GtkWidget *arrow2=gtk_image_new_from_file("images/arrow2.png");
    GtkWidget *arrow3=gtk_image_new_from_file("images/arrow3.png");
    gtk_button_set_image(GTK_BUTTON(rotatebutton[0]), arrow0);
    gtk_button_set_image(GTK_BUTTON(rotatebutton[1]), arrow1);
    gtk_button_set_image(GTK_BUTTON(rotatebutton[2]), arrow2);
    gtk_button_set_image(GTK_BUTTON(rotatebutton[3]), arrow3);
    
    for(int i=0; i<4; i++) {
        Coordinate *c = g_slice_new(Coordinate);
        c->x=i;
        g_signal_connect(rotatebutton[i], "clicked", G_CALLBACK(rotate_right), c);
    }
    
    GtkWidget *arrow4=gtk_image_new_from_file("images/arrow4.png");
    GtkWidget *arrow5=gtk_image_new_from_file("images/arrow5.png");
    GtkWidget *arrow6=gtk_image_new_from_file("images/arrow6.png");
    GtkWidget *arrow7=gtk_image_new_from_file("images/arrow7.png");
    gtk_button_set_image(GTK_BUTTON(rotatebutton[4]), arrow4);
    gtk_button_set_image(GTK_BUTTON(rotatebutton[5]), arrow5);
    gtk_button_set_image(GTK_BUTTON(rotatebutton[6]), arrow6);
    gtk_button_set_image(GTK_BUTTON(rotatebutton[7]), arrow7);
    
    for(int i=4; i<8; i++) {
        Coordinate *c = g_slice_new(Coordinate);
        c->x=i;
        g_signal_connect(rotatebutton[i], "clicked", G_CALLBACK(rotate_left), c);
    }
    
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            matrix[i][j]='0';
    
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            button[i][j]=gtk_button_new();
            gtk_widget_set_size_request(button[i][j], 45, 45);
            gtk_widget_set_name(button[i][j], "unpressed");
            gtk_grid_attach(GTK_GRID(grid), button[i][j], j+1, i+1, 1, 1);
        }
    }
    
    startbutton=gtk_button_new_with_label("I'll start");
    gtk_widget_set_name(startbutton, "start");
    gtk_grid_attach(GTK_GRID(grid2), startbutton, 0, 0, 1, 1);
    g_signal_connect(startbutton, "clicked", G_CALLBACK(start), NULL);
    
    giveupbutton=gtk_button_new_with_label("I give up");
    gtk_widget_set_name(giveupbutton, "additional");
    gtk_grid_attach(GTK_GRID(grid2), giveupbutton, 1, 0, 1, 1);
    g_signal_connect(giveupbutton, "clicked", G_CALLBACK(give_up), NULL);
    
    lock_buttons();
    lock_rotatebuttons();
    
    for(int i=0; i<6; i++) {
        for(int j=0; j<6; j++) {
            Coordinate *c = g_slice_new(Coordinate);
            c->x=i;
            c->y=j;
            g_signal_connect(button[i][j], "clicked", G_CALLBACK(clicked_button), c);
        }
    }
    
    box=gtk_box_new(TRUE, 15);
    gtk_box_pack_start(GTK_BOX(box), grid, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), grid2, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    
    g_timeout_add(100,refresh,NULL);
    
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(quit), (gpointer)window);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}


