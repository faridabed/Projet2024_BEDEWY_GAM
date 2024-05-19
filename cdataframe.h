#ifndef PROJET2024_BEDEWY_GAM_CDATAFRAME_H
#define PROJET2024_BEDEWY_GAM_CDATAFRAME_H

#include "column.h"

typedef struct {
    COLUMN** columns;       // Tableau de pointeurs vers les colonnes
    unsigned int size;      // Nombre actuel de colonnes
    unsigned int capacity;  // Capacité actuelle du tableau de colonnes
} CDATAFRAME;

CDATAFRAME* create_cdataframe();
void delete_cdataframe(CDATAFRAME** df);
void display_cdataframe(CDATAFRAME* df);
int add_column(CDATAFRAME* df, COLUMN* col);
void remove_column(CDATAFRAME* df, unsigned int index);
int add_row(CDATAFRAME* df, void** row_data); // Ajouter une ligne de données
void remove_row(CDATAFRAME* df, unsigned int row_index); // Supprimer une ligne de données
void rename_column(CDATAFRAME* df, unsigned int col_index, char* new_name); // Renommer une colonne
void display_partial_dataframe(CDATAFRAME* df, unsigned int start_row, unsigned int num_rows); // Afficher une partie du DataFrame
void display_column_names(CDATAFRAME* df); // Afficher les noms des colonnes
int find_value(CDATAFRAME* df, void* value); // Trouver une valeur dans le DataFrame
unsigned int count_rows(CDATAFRAME* df);
unsigned int count_columns(CDATAFRAME* df);
void fill_cdataframe_hardcoded(CDATAFRAME* df);
void replace_value_in_column(COLUMN* col, unsigned int index, void* new_value);
void demo_replace_value(CDATAFRAME* df, unsigned int col_index, unsigned int row_index, void* new_value);
unsigned int count_cells_meeting_condition(CDATAFRAME* df, int value, int (*condition)(int, int)); // fonction problematique
#endif //PROJET2024_BEDEWY_GAM_CDATAFRAME_H