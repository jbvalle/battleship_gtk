#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"
#include "../inc/battlefield.h"

#define COLS 10
#define ROWS 10


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
