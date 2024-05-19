#include "column.h"
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CDATAFRAME* create_cdataframe() {
    CDATAFRAME* df = (CDATAFRAME*) malloc(sizeof(CDATAFRAME));
    if (!df) return NULL;
    df->columns = NULL;
    df->size = 0;
    df->capacity = 0;
    return df;
}

void delete_cdataframe(CDATAFRAME** df) {
    if (!df || !*df) return;
    for (unsigned int i = 0; i < (*df)->size; i++) {
        delete_column(&((*df)->columns[i]));
    }
    free((*df)->columns);
    free(*df);
    *df = NULL;
}

void display_cdataframe(CDATAFRAME* df) {
    for (unsigned int i = 0; i < df->size; i++) {
        print_col(df->columns[i]);
    }
}

int add_column(CDATAFRAME* df, COLUMN* col) {
    if (df->size >= df->capacity) {
        df->capacity = (df->capacity == 0) ? 1 : df->capacity * 2;
        COLUMN** new_columns = (COLUMN**) realloc(df->columns, df->capacity * sizeof(COLUMN*));
        if (!new_columns) return 0;
        df->columns = new_columns;
    }
    df->columns[df->size++] = col;
    return 1;
}

void remove_column(CDATAFRAME* df, unsigned int index) {
    if (index >= df->size) return;
    delete_column(&df->columns[index]);
    for (unsigned int i = index; i < df->size - 1; i++) {
        df->columns[i] = df->columns[i + 1];
    }
    df->size--;
}

int add_row(CDATAFRAME* df, void** row_data) {
    for (unsigned int i = 0; i < df->size; i++) {
        if (!insert_value(df->columns[i], row_data[i])) {
            return 0;  // Handle rollback or continue as needed
        }
    }
    return 1;
}

void remove_row(CDATAFRAME* df, unsigned int row_index) {
    for (unsigned int i = 0; i < df->size; i++) {
        remove_value(df->columns[i], row_index);
    }
}

void rename_column(CDATAFRAME* df, unsigned int col_index, char* new_name) {
    if (col_index < df->size) {
        free(df->columns[col_index]->title);
        df->columns[col_index]->title = strdup(new_name);
    }
}

void display_partial_dataframe(CDATAFRAME* df, unsigned int start_row, unsigned int num_rows) {
    printf("Partial Display of DataFrame starting at row %d for %d rows:\n", start_row, num_rows);
    for (unsigned int i = 0; i < df->size; i++) {
        printf("Column %s:\n", df->columns[i]->title);
        for (unsigned int j = start_row; j < start_row + num_rows && j < df->columns[i]->size; j++) {
            char buffer[256];
            convert_value(df->columns[i], j, buffer, sizeof(buffer));
            printf("\t[%d] %s\n", j, buffer);
        }
    }
}

void display_column_names(CDATAFRAME* df) {
    printf("Column Names:\n");
    for (unsigned int i = 0; i < df->size; i++) {
        printf("%d: %s\n", i, df->columns[i]->title);
    }
}

int find_value(CDATAFRAME* df, void* value) {
    for (unsigned int i = 0; i < df->size; i++) {
        for (unsigned int j = 0; j < df->columns[i]->size; j++) {
            if (df->columns[i]->column_type == STRING && strcmp(df->columns[i]->data[j].string_value, value) == 0) {
                return 1;
            } else if (df->columns[i]->column_type == INT && df->columns[i]->data[j].int_value == *(int*)value) {
                return 1;
            }
        }
    }
    return 0;
}

// Compter les lignes dans le CDataframe
unsigned int count_rows(CDATAFRAME* df) {
    if (df->size == 0) return 0;
    return df->columns[0]->size; // Supposant que toutes les colonnes ont le même nombre de lignes
}

// Compter les colonnes dans le CDataframe
unsigned int count_columns(CDATAFRAME* df) {
    return df->size;
}

// Fonction pour compter les cellules répondant à une condition spécifique
unsigned int count_cells_meeting_condition(CDATAFRAME* df, int value, int (*condition)(int, int)) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < df->size; i++) {
        for (unsigned int j = 0; j < df->columns[i]->size; j++) {
            int cell_value;
            // On suppose que nous comparons des entiers ici
            if (df->columns[i]->column_type == INT) {
                cell_value = df->columns[i]->data[j].int_value;
                if (condition(cell_value, value)) {
                    count++;
                }
            }
        }
    }
    return count;
}

void fill_cdataframe_hardcoded(CDATAFRAME* df) {
    if (df == NULL) {
        printf("Erreur: DataFrame non initialisé.\n");
        return;
    }

    // Créer et ajouter des colonnes de différents types
    COLUMN* col_int = create_column(INT, "Age");
    COLUMN* col_float = create_column(FLOAT, "Taille");
    COLUMN* col_char = create_column(CHAR, "Initiale");
    COLUMN* col_string = create_column(STRING, "Nom");

    add_column(df, col_int);
    add_column(df, col_float);
    add_column(df, col_char);
    add_column(df, col_string);

    // Données prédéfinies à insérer
    int ages[] = {25, 30, 35};
    float tailles[] = {1.75f, 1.80f, 1.85f};
    char initiales[] = {'A', 'B', 'C'};
    char* noms[] = {"Alice", "Bob", "Charlie"};

    // Insertion des données dans chaque colonne
    for (int i = 0; i < 3; i++) {
        insert_value(col_int, &ages[i]);
        insert_value(col_float, &tailles[i]);
        insert_value(col_char, &initiales[i]);
        insert_value(col_string, noms[i]);
    }
}

// Remplace la valeur dans une colonne spécifique à un index donné
void replace_value_in_column(COLUMN* col, unsigned int index, void* new_value) {
    if (col == NULL) {
        printf("Erreur: La colonne n'est pas initialisée.\n");
        return;
    }
    if (index >= col->size) {
        printf("Erreur: Index hors limites.\n");
        return;
    }

    switch (col->column_type) {
        case INT:
            col->data[index].int_value = *(int*)new_value;
            break;
        case FLOAT:
            col->data[index].float_value = *(float*)new_value;
            break;
        case CHAR:
            col->data[index].char_value = *(char*)new_value;
            break;
        case STRING:
            free(col->data[index].string_value); // Libérer la mémoire de l'ancienne chaîne
            col->data[index].string_value = strdup((char*)new_value);
            break;
        default:
            printf("Type non supporté pour le remplacement.\n");
    }
}

// Fonction d'aide pour démontrer l'utilisation
void demo_replace_value(CDATAFRAME* df, unsigned int col_index, unsigned int row_index, void* new_value) {
    if (df == NULL || col_index >= df->size) {
        printf("Erreur: DataFrame non initialisé ou index de colonne invalide.\n");
        return;
    }

    replace_value_in_column(df->columns[col_index], row_index, new_value);
}
