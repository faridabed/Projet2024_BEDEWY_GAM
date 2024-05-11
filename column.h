#ifndef PROJET2024_BEDEWY_GAM_COLUMN_H
#define PROJET2024_BEDEWY_GAM_COLUMN_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des types de données pouvant être stockés dans les colonnes.
typedef enum enum_type {
    NILVAL = 1, // Valeur nulle
    UINT,       // Entier non signé
    INT,        // Entier signé
    CHAR,       // Caractère
    FLOAT,      // Flottant simple précision
    DOUBLE,     // Flottant double précision
    STRING,     // Chaîne de caractères
    STRUCTURE   // Structure (pointeur générique)
} ENUM_TYPE;

// Union permettant de stocker n'importe quel type de donnée dans la colonne.
typedef union {
    unsigned int uint_value;
    int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
} COL_TYPE;

// Structure représentant une colonne de données.
typedef struct column {
    char* title;                   // Titre de la colonne
    unsigned int size;             // Taille logique de la colonne
    unsigned int max_size;         // Taille physique maximale de la colonne
    ENUM_TYPE column_type;         // Type des données de la colonne
    COL_TYPE* data;                // Tableau de données stockées
    unsigned long long int* index; // Tableau d'indices pour des fonctionnalités avancées (non utilisé ici)
} COLUMN;

// Prototypes de fonctions pour la gestion des colonnes
COLUMN* create_column(ENUM_TYPE type, char* title);
int insert_value(COLUMN* col, void* value);
void delete_column(COLUMN** col);
void print_col(COLUMN* col);
void convert_value(COLUMN* col, unsigned long long int i, char* str, size_t size);

void remove_value(COLUMN* col, unsigned int index);
void menu();

#endif PROJET2024_BEDEWY_GAM_COLUMN_H
