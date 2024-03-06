// 2_base.c

#include <gtk/gtk.h>
#include <string.h>
#include "1_attribut.h"
#include "3_verification.h"
#include "4_inscription.h"  // Ajout de l'inclusion du fichier d'inscription

GtkWidget *idProfEntry;

void base_window_valider(GtkWidget *widget, gpointer data) {
    const gchar *idProf = gtk_entry_get_text(GTK_ENTRY(idProfEntry));
    (void)widget;
    (void)data;

    // Appel de la fonction de vérification
    if (verifier_id_prof(idProf)) {
        g_print("ID Prof saisi existe dans le fichier ID_Profs.txt : %s\n", idProf);
        // Ajoutez ici le code que vous souhaitez exécuter lorsque l'ID existe
    } else {
        g_print("ID Prof saisi n'existe pas dans le fichier ID_Profs.txt : %s\n", idProf);
        // Ajoutez ici le code que vous souhaitez exécuter lorsque l'ID n'existe pas
    }
}

void inscription(GtkWidget *widget, gpointer data) {
    (void)widget;
    (void)data;

    // Détruire la fenêtre courante
    gtk_widget_destroy(GTK_WIDGET(data));

    // Ouvrir la fenêtre d'inscription
    inscription_window(0, NULL);  // Vous devrez peut-être ajuster les arguments en fonction de votre implémentation
}

void base_window(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    idProfEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), idProfEntry, 0, 0, 1, 1);

    validerButton = gtk_button_new_with_label("Valider");
    g_signal_connect(validerButton, "clicked", G_CALLBACK(base_window_valider), window);
    gtk_grid_attach(GTK_GRID(grid), validerButton, 1, 0, 1, 1);

    inscriptionButton = gtk_button_new_with_label("Inscription");
    g_signal_connect(inscriptionButton, "clicked", G_CALLBACK(inscription), window);
    gtk_grid_attach(GTK_GRID(grid), inscriptionButton, 2, 0, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();
}