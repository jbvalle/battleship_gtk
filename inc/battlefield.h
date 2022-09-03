#ifndef BATTLE_FIELD_H
#define BATTLE_FIELD_H
#define COLS 10
#define ROWS 10

#include "../gtk/gtk.h"


typedef struct Battlefield{

    GtkWidget *window;

    GtkWidget *entry[ROWS * COLS];
    GtkWidget *hbox[ROWS];
    GtkWidget *vbox;

    GtkWidget *hbox_input;
    GtkWidget *entry_input;
    GtkWidget *button_input;
    char *user_entry_text;
    int row_coord;
    int col_coord;

}Battlefield;

GtkWidget *init_window(Battlefield *battlefield);

#endif