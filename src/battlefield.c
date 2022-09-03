#include <stdio.h>
#include "gtk/gtk.h"
#include "../inc/battlefield.h"
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#define COLS 10
#define ROWS 10

void get_user_entry_text(GtkWidget *widget, gpointer data){

        UNUSED(widget);

        Battlefield *battlefield_instance = data;

        battlefield_instance->user_entry_text = (char *) malloc(4);

        // Get User Input Coordinate -> Assign to variable
        strcpy(battlefield_instance->user_entry_text, gtk_entry_get_text(GTK_ENTRY(battlefield_instance->entry_input)) );
        
        /*****************************************************************************/
        /** Assign Coordinates fetched from Entry Input to seperate X,Y Coordinates **/
        /*****************************************************************************/

        battlefield_instance->row_coord = battlefield_instance->user_entry_text[0];
        battlefield_instance->col_coord = (int)strtol(&(battlefield_instance->user_entry_text[1]), NULL, 10);

        /*****************************************************/
        /** Check for Deployed Ship, aka if entry_text == 1 **/
        /*****************************************************/

        int targeted_coordinate = (battlefield_instance->row_coord - 65) * COLS + (battlefield_instance->col_coord - 1);

        int ship_deployed = (int)strtol(gtk_entry_get_text(GTK_ENTRY(battlefield_instance->entry[targeted_coordinate])), NULL, 10);

        if(ship_deployed == 1){

            gtk_entry_set_text(GTK_ENTRY(battlefield_instance->entry[targeted_coordinate]), "X");

            GtkWidget *alert_window = gtk_message_dialog_new(GTK_WINDOW(battlefield_instance->window),
                                                            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT |
                                                            GTK_DIALOG_USE_HEADER_BAR,
                                                            GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE,
                                                            "SHIP WAS HIT");
            gtk_widget_set_name(alert_window, "alert_window");
            gtk_dialog_run(GTK_DIALOG(alert_window));
            gtk_widget_destroy(alert_window);
        }

        

        free(battlefield_instance->user_entry_text);
}

GtkWidget *init_window(Battlefield *battlefield){

    /*****************/
    /** Main Window **/
    /*****************/

    // 1. Initialize main window 
    battlefield->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // 2. Add main quit callback
    g_signal_connect(battlefield->window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    /**********************/
    /** Battlefield Grid **/
    /**********************/

    // 1. Initialize Horizontal GTK Containers
    for(int i = 0; i < ROWS; i++){
        battlefield->hbox[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); gtk_box_set_homogeneous(GTK_BOX(battlefield->hbox[i]), TRUE);
    }

    // 2. Initialize MAIN Vertical  GTK Containers -> All Child Containers will be packed into this Container
    battlefield->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); gtk_box_set_homogeneous(GTK_BOX(battlefield->vbox), TRUE);


    // 3. Initialize GTK Entries Grid
    for(int i = 0; i < ROWS*COLS; i++)battlefield->entry[i] = gtk_entry_new();

    // 4. Add Grid Entry Widgets to Horizontal Containers
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            
            gtk_box_pack_start(GTK_BOX(battlefield->hbox[i]),battlefield->entry[i * COLS + j], 0, 0, 0); 

            gtk_entry_set_width_chars(GTK_ENTRY(battlefield->entry[i * COLS + j]), 4);

            gtk_entry_set_max_length(GTK_ENTRY(battlefield->entry[i * COLS + j]), 4);
        }
    }

    // 5. Add All Horizontal Containers to MAIN Vertical Container
    for(int i = 0; i < ROWS; i++)gtk_box_pack_start(GTK_BOX(battlefield->vbox), battlefield->hbox[i], 0, 0, 0);


    // 6. Add Placeholder Text to entries
    char *row_index[]={
        "A\0",
        "B\0",
        "C\0",
        "D\0",
        "E\0",
        "F\0",
        "G\0",
        "H\0",
        "I\0",
        "J\0"
    };

    for(int i = 0; i < ROWS; i++){

        for(int j = 0; j < COLS; j++){

            char col_index[2]; bzero(col_index, sizeof(col_index));
            char tmp_num_index[2];

            sprintf(tmp_num_index, "%d", j + 1);
            strcpy(col_index, row_index[i]); 
            strcat(col_index, tmp_num_index);

            gtk_entry_set_placeholder_text(GTK_ENTRY(battlefield->entry[i * COLS + j]), col_index);
        }
    }
    /***********************************/
    /** User Input & Button Interface **/
    /***********************************/


    // 1. Initialize Horizontal Container for Button and Entry Widget
    battlefield->hbox_input = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); gtk_box_set_homogeneous(GTK_BOX(battlefield->hbox_input), TRUE);



    // 2. Initialize User input and user button
    battlefield->entry_input  = gtk_entry_new();         
    gtk_entry_set_placeholder_text(GTK_ENTRY(battlefield->entry_input), "Enter Coordinates");

    battlefield->button_input = gtk_button_new_with_label("Generate");


    // 3. ADD Input and button instance to container
    gtk_box_pack_start(GTK_BOX(battlefield->hbox_input), battlefield->entry_input, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(battlefield->hbox_input), battlefield->button_input, 1, 1, 10);

    
    gtk_widget_set_name(battlefield->entry_input, "entry_input");

    GtkStyleContext *context = gtk_widget_get_style_context(battlefield->entry_input);
        
    gtk_style_context_add_class(context,"button_input");



    // 4. Add Userinterface container to Parent Main Vertical Container
    gtk_box_pack_start(GTK_BOX(battlefield->vbox), battlefield->hbox_input, 0, 0, 0); 

    // 5. Assign Function calls to widgets
    g_signal_connect(battlefield->button_input, "clicked", G_CALLBACK(get_user_entry_text), battlefield);

    /*******************************************************/
    /** Add all Widgets to main Window and set visibility **/
    /*******************************************************/

    gtk_window_set_default_size(GTK_WINDOW(battlefield->window), 300, 300);

    gtk_container_add(GTK_CONTAINER(battlefield->window), battlefield->vbox);

    gtk_widget_show_all(battlefield->window);
    return battlefield->window;
}