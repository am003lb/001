// 4_inscription.h

#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include "1_attribut.h"
#include <gtk/gtk.h>

extern GtkWidget *validerButton;
extern GtkWidget *inscriptionButton;

void inscription_window(int argc, char *argv[]);
void annuler_inscription(GtkWidget *widget, gpointer data);

#endif