#ifndef PROJET2024_BEDEWY_GAM_CDATAFRAME_H
#define PROJET2024_BEDEWY_GAM_CDATAFRAME_H

#include "column.h"

// Structure représentant un DataFrame contenant un tableau de colonnes.
typedef struct {
    COLUMN** columns;       // Tableau de pointeurs vers les colonnes
    unsigned int size;      // Nombre actuel de colonnes
    unsigned int capacity;  // Capacité actuelle du tableau de colonnes
} CDATAFRAME;

// Crée un nouveau DataFrame vide.
CDATAFRAME* create_cdataframe();

// Supprime un DataFrame et libère toutes les ressources associées.
void delete_cdataframe(CDATAFRAME** df);

// Affiche le contenu complet d'un DataFrame.
void display_cdataframe(CDATAFRAME* df);

// Ajoute une colonne au DataFrame.
int add_column(CDATAFRAME* df, COLUMN* col);

// Supprime une colonne du DataFrame.
void remove_column(CDATAFRAME* df, unsigned int index);

// Ajoute une ligne de données au DataFrame.
int add_row(CDATAFRAME* df, void** row_data);

// Supprime une ligne de données du DataFrame.
void remove_row(CDATAFRAME* df, unsigned int row_index);

// Renomme une colonne dans le DataFrame.
void rename_column(CDATAFRAME* df, unsigned int col_index, char* new_name);

// Affiche une partie spécifiée du DataFrame.
void display_partial_dataframe(CDATAFRAME* df, unsigned int start_row, unsigned int num_rows);

// Affiche les noms de toutes les colonnes du DataFrame.
void display_column_names(CDATAFRAME* df);

// Trouve une valeur spécifique dans le DataFrame.
int find_value(CDATAFRAME* df, void* value);

// Compte le nombre total de lignes dans le DataFrame.
unsigned int count_rows(CDATAFRAME* df);

// Compte le nombre total de colonnes dans le DataFrame.
unsigned int count_columns(CDATAFRAME* df);

// Remplit le DataFrame avec des données pré-définies pour des démonstrations.
void fill_cdataframe_hardcoded(CDATAFRAME* df);

// Remplace une valeur dans une colonne du DataFrame.
void replace_value_in_column(COLUMN* col, unsigned int index, void* new_value);

// Démonstration du remplacement d'une valeur spécifique dans une colonne du DataFrame.
void demo_replace_value(CDATAFRAME* df, unsigned int col_index, unsigned int row_index, void* new_value);

// Compte les cellules qui répondent à une condition spécifique.
unsigned int count_cells_meeting_condition(CDATAFRAME* df, int value, int (*condition)(int, int));

// Type de fonction pour les fonctions conditionnelles qui prennent deux entiers.
typedef int (*condition_func_int)(int, int);
#endif //PROJET2024_BEDEWY_GAM_CDATAFRAME_H