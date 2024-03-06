// 4_inscription.c

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "1_attribut.h"

#include "4_inscription.h"
#include "2_base.h"

// Définition des variables
GtkWidget *validerButton;
GtkWidget *inscriptionButton;

GtkWidget *idProfLabel;
GtkWidget *nomProfEntry;
GtkWidget *prenomProfEntry;
GtkWidget *ageProfEntry;
GtkWidget *matieresComboBox;
GtkWidget *validerButton;
GtkWidget *annulerButton;

void generate_random_id(char *id, int size) {
    srand(time(NULL));
    snprintf(id, size, "%04d", rand() % 10000);
}

// Fonction pour récupérer l'ID de la matière à partir du fichier
char *get_matiere_id(const char *selectedMatiere) {
    FILE *file = fopen("0_ID_matieres.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier 0_ID_matieres.txt");
        return NULL;
    }

    char line[MAX_STRING_SIZE];
    static char matiereId[MAX_STRING_SIZE];  // Déclaré comme statique pour la conservation de la mémoire
    while (fgets(line, sizeof(line), file) != NULL) {
        strtok(line, "\n");
        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(matiereId, token);
            token = strtok(NULL, ",");
            if (token != NULL && strcmp(token, selectedMatiere) == 0) {
                fclose(file);
                return matiereId;
            }
        }
    }

    fclose(file);
    return NULL;  // Matière non trouvée
}

void load_matieres_from_file(GtkComboBoxText *comboBox) {
    FILE *file = fopen("0_ID_matieres.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_STRING_SIZE];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Vous pouvez ajuster cette ligne en fonction du format de votre fichier matières
        strtok(line, "\n");  // Supprime le saut de ligne à la fin

        // Utiliser strtok pour extraire le nom de la matière (deuxième élément)
        char *token = strtok(line, ", ");
        if (token != NULL) {
            token = strtok(NULL, ",");
            if (token != NULL) {
                gtk_combo_box_text_append_text(comboBox, token);
            }
        }
    }

    fclose(file);
}

void valider_inscription(GtkWidget *widget, gpointer data) {
    const gchar *nomProfText = gtk_entry_get_text(GTK_ENTRY(nomProfEntry));
    const gchar *prenomProfText = gtk_entry_get_text(GTK_ENTRY(prenomProfEntry));
    const gchar *ageProfText = gtk_entry_get_text(GTK_ENTRY(ageProfEntry));
    const gchar *selectedMatiere = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(matieresComboBox));

    // Vérifier si les champs sont vides
    if (strlen(nomProfText) == 0 || strlen(prenomProfText) == 0 || strlen(ageProfText) == 0 || selectedMatiere == NULL) {
        g_print("Veuillez remplir tous les champs avant de valider.\n");
        return;
    }

    char idProf[MAX_ID_SIZE];
    generate_random_id(idProf, sizeof(idProf));

    // Récupération de l'ID de la matière
    char *matiereId = get_matiere_id(selectedMatiere);

    if (matiereId != NULL) {
        // Enregistrement des données dans le fichier 0_ID_Profs.txt
        FILE *file = fopen("0_ID_Profs.txt", "a");
        if (file != NULL) {
            fprintf(file, "%s, %s, %s, %s, %s\n", idProf, matiereId, nomProfText, prenomProfText, ageProfText);
            fclose(file);
            g_print("Inscription réussie.\n");

            // Détruire la fenêtre courante
            gtk_widget_destroy(GTK_WIDGET(data));

            // Rediriger vers base_window après la validation réussie
            base_window(0, NULL);  // Assurez-vous que ces arguments sont appropriés à votre implémentation
        } else {
            perror("Erreur lors de l'ouverture du fichier 0_ID_Profs.txt");
            g_print("Échec de l'inscription.\n");
        }
    } else {
        g_print("Erreur : ID de matière introuvable.\n");
    }
}

void annuler_inscription(GtkWidget *widget, gpointer data) {
    g_print("Inscription annulée.\n");
    
    // Fermer la fenêtre d'inscription
    gtk_widget_destroy(GTK_WIDGET(data));
    
    // Ouvrir la fenêtre principale
    base_window(0, NULL);  // Vous devrez peut-être ajuster les arguments en fonction de votre implémentation
}

void inscription_window(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    idProfLabel = gtk_label_new("ID Prof: ");
    gtk_grid_attach(GTK_GRID(grid), idProfLabel, 0, 0, 1, 1);

    nomProfEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), nomProfEntry, 1, 0, 1, 1);

    prenomProfEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), prenomProfEntry, 2, 0, 1, 1);

    ageProfEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), ageProfEntry, 3, 0, 1, 1);

    // Ajout de la liste déroulante pour les matières
    matieresComboBox = gtk_combo_box_text_new();

    // Chargement des matières depuis le fichier
    load_matieres_from_file(GTK_COMBO_BOX_TEXT(matieresComboBox));

    gtk_grid_attach(GTK_GRID(grid), matieresComboBox, 4, 0, 1, 1);

    validerButton = gtk_button_new_with_label("Valider");
    g_signal_connect(validerButton, "clicked", G_CALLBACK(valider_inscription), window);
    gtk_grid_attach(GTK_GRID(grid), validerButton, 5, 0, 1, 1);

    annulerButton = gtk_button_new_with_label("Annuler");
    g_signal_connect(annulerButton, "clicked", G_CALLBACK(annuler_inscription), window);
    gtk_grid_attach(GTK_GRID(grid), annulerButton, 6, 0, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();
}