#ifndef PROJET2024_BEDEWY_GAM_COLUMN_H
#define PROJET2024_BEDEWY_GAM_COLUMN_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Définition des types de données pouvant être stockés dans les colonnes.
typedef enum enum_type {
    NILVAL = 1,    // Valeur nulle, utilisée pour des entrées non définies.
    UINT,          // Entier non signé
    INT,           // Entier signé
    CHAR,          // Caractère
    FLOAT,         // Flottant simple précision
    DOUBLE,        // Flottant double précision
    STRING,        // Chaîne de caractères
    STRUCTURE      // Structure, utilisée pour des types complexes (pointeur générique)
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
    unsigned int size;             // Nombre d'éléments stockés actuellement
    unsigned int max_size;         // Capacité maximale de la colonne
    ENUM_TYPE column_type;         // Type de données stockées dans la colonne
    COL_TYPE* data;                // Tableau de données stockées
    unsigned long long int* index; // Tableau d'indices pour des fonctionnalités avancées (optionnel)
} COLUMN;

// Prototypes de fonctions pour la gestion des colonnes
COLUMN* create_column(ENUM_TYPE type, char* title); // Crée une nouvelle colonne
int insert_value(COLUMN* col, void* value);         // Insère une valeur dans la colonne
void delete_column(COLUMN** col);                   // Supprime une colonne et libère la mémoire associée
void print_col(COLUMN* col);                        // Affiche les valeurs dans la colonne
void convert_value(COLUMN* col, unsigned long long int i, char* str, size_t size); // Convertit une valeur en chaîne de caractères

void remove_value(COLUMN* col, unsigned int index); // Supprime une valeur à un index spécifié
void menu(); // Prototype pour une fonction de menu (doit être définie ailleurs)

#endif PROJET2024_BEDEWY_GAM_COLUMN_H
