#ifndef PROJET2024_BEDEWY_GAM_MENU_H
#define PROJET2024_BEDEWY_GAM_MENU_H

#include "cdataframe.h"


// menu
void menu();
void row_menu(CDATAFRAME* df);
void column_menu(CDATAFRAME* df);
void display_menu(CDATAFRAME* df);
void insert_value_into_column(COLUMN* col);
void add_row_to_dataframe(CDATAFRAME* df);
#endif //PROJET2024_BEDEWY_GAM_MENU_H

