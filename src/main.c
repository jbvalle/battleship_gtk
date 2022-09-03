#include <stdio.h>
#include "../gtk/gtk.h"
#include "../inc/battlefield.h"

#define COLS 10
#define ROWS 10

/*
void get_row_entry_input(GtkWidget *button, gpointer data) {
    
    if (data == NULL)
        return;

    MyWidget *myWidget = data;
    myWidget->row = convert_str_to_int(gtk_entry_get_text(GTK_ENTRY(myWidget->row_entry_input)));
}
*/



int main(int argc, char **argv){

    // Initialize gtk
    gtk_init(&argc, &argv);

    // Initialize battlefield instance
    Battlefield battlefield;

    // Configure Battlefield instance
    init_window(&battlefield);


    gtk_main();

    return 0;
}
