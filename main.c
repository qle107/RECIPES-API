#include <gtk/gtk.h>
#include "login_interface.h"
#include "apiFood.h"
#include "splitString.h"
typedef struct {
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *box; // Work as grid in HTML
    GtkWidget *query_entry; //Store query
    GtkWidget *url_entry; //Store API
    GtkWidget *token_entry; //Store token
    GtkWidget *addition_entry; //Store addition
} LoginData;

static void submit_button_clicked(GtkWidget *widget, gpointer data) {
    LoginData *login_data = (LoginData *)data;
    const gchar *query = gtk_entry_get_text(GTK_ENTRY(login_data->query_entry));
    const gchar *urlRecom = gtk_entry_get_text(GTK_ENTRY(login_data->url_entry));
    const gchar *apiKey = gtk_entry_get_text(GTK_ENTRY(login_data->token_entry));
    const gchar *addition = gtk_entry_get_text(GTK_ENTRY(login_data->addition_entry));

    // Call food api and split it to String
    char* result = splitString(foodAPI(query,urlRecom,apiKey,addition));

    // Create a new tab to display the result
    GtkWidget *result_label = gtk_label_new(result);

    // Remove any existed result
    GList *children = gtk_container_get_children(GTK_CONTAINER(login_data->box));
    while (children != NULL) {
        GtkWidget *child = children->data;
        if (GTK_IS_LABEL(child)) {
            gtk_container_remove(GTK_CONTAINER(login_data->box), child);
        }
        children = g_list_next(children);
    }

    // Add the new result
    gtk_box_pack_start(GTK_BOX(login_data->box), result_label, FALSE, FALSE, 0);

    // Show all
    gtk_widget_show_all(login_data->box);

    free(result);
}


static void login_button_clicked(GtkWidget *widget, gpointer data) {
    LoginData *login_data = (LoginData *)data;
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(login_data->username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(login_data->password_entry));

    if (verifyUser(username, password)) {
        // Remove login button
        gtk_widget_destroy(widget);

        // Create new grid
        GtkWidget *grid = gtk_grid_new();
        gtk_box_pack_start(GTK_BOX(login_data->box), grid, TRUE, TRUE, 0);

        // Add query label
        GtkWidget *query_label = gtk_label_new("Enter your query:");
        gtk_grid_attach(GTK_GRID(grid), query_label, 0, -2, 1, 1);

        // Add query entry
        login_data->query_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), login_data->query_entry, 1, -2, 1, 1);

        // Add URL label
        GtkWidget *url_label = gtk_label_new("Enter the URL:");
        gtk_grid_attach(GTK_GRID(grid), url_label, 0, -3, 1, 1);

        // Add URL entry
        login_data->url_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), login_data->url_entry, 1, -3, 1, 1);

        // Add Addition label
        GtkWidget *addition_label = gtk_label_new("Enter the addition:");
        gtk_grid_attach(GTK_GRID(grid), addition_label, 0, 0, 1, 1);

        // Add Addition entry
        login_data->addition_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), login_data->addition_entry, 1, 0, 1, 1);

        // Add Token label
        GtkWidget *token_label = gtk_label_new("Enter the Token:");
        gtk_grid_attach(GTK_GRID(grid), token_label, 0, -1, 1, 1);

        // Add Token entry
        login_data->token_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), login_data->token_entry, 1, -1, 1, 1);


        // Add submit button
        GtkWidget *submit_button = gtk_button_new_with_label("Submit");
        gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 2, 2, 1);
        g_signal_connect(submit_button, "clicked", G_CALLBACK(submit_button_clicked), login_data);

        // Show all newly added widgets
        gtk_widget_show_all(grid);
    }
}


static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    // Initialize the GTK+ libraries
    gtk_init(&argc, &argv);

    // Define variables
    GtkWidget *window;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *login_button;
    GtkWidget *grid;
    GtkWidget *box; // Container to hold the grids

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Set app title
    gtk_window_set_title(GTK_WINDOW(window), "Login");

    // Set window size
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);

    username_label = gtk_label_new("Username:");
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    password_label = gtk_label_new("Password:");
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);

    username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 100, 1);

    password_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 100, 1);
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    LoginData login_data;
    login_data.username_entry = username_entry;
    login_data.password_entry = password_entry;
    login_data.box = box;

    // Add login button
    login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(login_button_clicked), &login_data);
    gtk_grid_attach(GTK_GRID(grid), login_button, 2, 2, 50, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
