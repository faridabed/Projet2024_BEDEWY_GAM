// column.c
#include "column.h"

//
// Crée une nouvelle colonne
COLUMN* create_column(ENUM_TYPE type, char* title) {
    COLUMN* col = (COLUMN*) malloc(sizeof(COLUMN));
    if (col == NULL) return NULL;
    col->title = strdup(title); // Allocation de memoire pour chaine de caractere
    col->size = 0;
    col->max_size = 256;  // Taille physique initiale
    col->column_type = type;
    col->data = (COL_TYPE*) calloc(col->max_size, sizeof(COL_TYPE));
    col->index = NULL;
    return col;
}

// Insère une valeur dans la colonne
int insert_value(COLUMN* col, void* value) {
    if (col->size >= col->max_size) {
        // Réallouer plus d'espace
        col->max_size += 256;
        col->data = (COL_TYPE*) realloc(col->data, col->max_size * sizeof(COL_TYPE));
        if (col->data == NULL) return 0;
    }
    switch (col->column_type) {
        case INT:
            col->data[col->size].int_value = *(int*) value;
            break;
        case CHAR:
            col->data[col->size].char_value = *(char*) value;
            break;
        case FLOAT:
            col->data[col->size].float_value = *(float*) value;
            break;
        case DOUBLE:
            col->data[col->size].double_value = *(double*) value;
            break;
        case STRING:
            col->data[col->size].string_value = strdup((char*) value);
            break;
        case STRUCTURE:
        case NILVAL:
            col->data[col->size].struct_value = value;
            break;
    }
    col->size++;
    return 1;
}

// Supprime une colonne et libère la mémoire allouée
void delete_column(COLUMN** col) {
    if ((*col)->column_type == STRING) {
        for (unsigned int i = 0; i < (*col)->size; i++) {
            free((*col)->data[i].string_value);
        }
    }
    free((*col)->data);
    free((*col)->title);
    free(*col);
    *col = NULL;
}

// Affiche le contenu de la colonne
void print_col(COLUMN* col) {
    printf("Colonne : %s\n", col->title);
    for (unsigned int i = 0; i < col->size; i++) {
        char buffer[128];
        convert_value(col, i, buffer, sizeof(buffer));
        printf("[%d] %s\n", i, buffer);
    }
}

// Convertit une valeur de la colonne en chaîne de caractères
void convert_value(COLUMN* col, unsigned long long int i, char* str, size_t size) {
    switch (col->column_type) {
        case INT:
            snprintf(str, size, "%d", col->data[i].int_value);
            break;
        case CHAR:
            snprintf(str, size, "%c", col->data[i].char_value);
            break;
        case FLOAT:
            snprintf(str, size, "%.2f", col->data[i].float_value);
            break;
        case DOUBLE:
            snprintf(str, size, "%.2lf", col->data[i].double_value);
            break;
    }
}

void remove_value(COLUMN* col, unsigned int index) {
    if (index >= col->size) return; // Vérifier que l'index est valide
    // Déplacer tous les éléments après l'index vers la gauche pour supprimer l'élément
    for (unsigned int i = index; i < col->size - 1; i++) {
        col->data[i] = col->data[i + 1];
    }
    col->size--; // Réduire la taille logique de la colonne
}