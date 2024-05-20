#ifndef PROJET2024_BEDEWY_GAM_MENU_H
#define PROJET2024_BEDEWY_GAM_MENU_H

#include "cdataframe.h"


//Affiche le menu principal de l'application.
void menu();

//Affiche le menu pour la gestion des lignes dans un dataframe.
void row_menu(CDATAFRAME* df);

//Affiche le menu pour la gestion des colonnes dans un dataframe.
void column_menu(CDATAFRAME* df);

// Affiche le menu pour les options d'affichage des données dans le dataframe.
void display_menu(CDATAFRAME* df);

//Permet à l'utilisateur d'insérer une valeur dans une colonne spécifiée.
void insert_value_into_column(COLUMN* col);

//Permet à l'utilisateur d'ajouter une ligne de données au dataframe.
void add_row_to_dataframe(CDATAFRAME* df);

#endif //PROJET2024_BEDEWY_GAM_MENU_H

