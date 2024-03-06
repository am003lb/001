// 1_attribut.h

#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#define MAX_STRING_SIZE 50
#define MAX_ID_SIZE 10
#define MAX_NOTE_SIZE 5

typedef struct {
    char idProf[MAX_ID_SIZE];
    char idMatiere[MAX_ID_SIZE];
    char nomProf[MAX_STRING_SIZE];
    char prenomProf[MAX_STRING_SIZE];
    char ageProf[MAX_ID_SIZE];
} Prof;

typedef struct {
    char idMatiere[MAX_ID_SIZE];
    char nomMatiere[MAX_STRING_SIZE];
} Matiere;

typedef struct {
    char idEleve[MAX_ID_SIZE];
    char nomEleve[MAX_STRING_SIZE];
    char prenomEleve[MAX_STRING_SIZE];
    char ageEleve[MAX_ID_SIZE];
    char nomMatiere[MAX_STRING_SIZE];
    char noteEleve[MAX_NOTE_SIZE];
} Eleve;

#endif