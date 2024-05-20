#include "column.h"


// Crée une colonne en allouant la mémoire nécessaire et initialise ses attributs.
COLUMN* create_column(ENUM_TYPE type, char* title) {
    COLUMN* col = (COLUMN*) malloc(sizeof(COLUMN));
    if (col == NULL) return NULL;  // Vérifie l'échec de l'allocation
    col->title = strdup(title); // Duplique le titre pour gestion propre de la mémoire
    col->size = 0;
    col->max_size = 256;  // Définit la taille initiale de la colonne
    col->column_type = type;
    col->data = (COL_TYPE*) calloc(col->max_size, sizeof(COL_TYPE));
    col->index = NULL;  // Initialement, aucun index n'est utilisé
    return col;
}

// Insère une valeur dans une colonne en gérant le type et la capacité.
int insert_value(COLUMN* col, void* value) {
    if (col->size >= col->max_size) {
        col->max_size += 256; // Augmente la capacité si nécessaire
        col->data = (COL_TYPE*) realloc(col->data, col->max_size * sizeof(COL_TYPE));
        if (col->data == NULL) return 0;  // Gère l'échec de realloc
    }
    // Insertion basée sur le type de données
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
            col->data[col->size].string_value = strdup((char*) value);  // Duplique la chaîne
            break;
        case STRUCTURE:
        case NILVAL:
            col->data[col->size].struct_value = value;
            break;
    }
    col->size++;
    return 1;
}


// Supprime une colonne, libérant la mémoire pour toutes les données stockées.
void delete_column(COLUMN** col) {
    if ((*col)->column_type == STRING) {
        for (unsigned int i = 0; i < (*col)->size; i++) {
            free((*col)->data[i].string_value);  // Libère chaque chaîne individuellement
        }
    }
    free((*col)->data);
    free((*col)->title);
    free(*col);
    *col = NULL;
}


// Affiche toutes les valeurs d'une colonne.
void print_col(COLUMN* col) {
    printf("Colonne : %s\n", col->title);
    for (unsigned int i = 0; i < col->size; i++) {
        char buffer[128];
        convert_value(col, i, buffer, sizeof(buffer));
        printf("[%d] %s\n", i, buffer);
    }
}

// Convertit et formatte une valeur de la colonne pour l'affichage.
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

// Supprime une valeur d'une colonne en décalant les éléments restants.
void remove_value(COLUMN* col, unsigned int index) {
    if (index >= col->size) {
        printf("Erreur : Index hors limites.\n");
        return; // Vérifier que l'index est valide avant de continuer
    }

    // Si la colonne stocke des chaînes de caractères, libère la mémoire allouée
    if (col->column_type == STRING) {
        free(col->data[index].string_value);
    }

    // Déplacer tous les éléments après l'index vers la gauche pour supprimer l'élément
    for (unsigned int i = index; i < col->size - 1; i++) {
        col->data[i] = col->data[i + 1];
    }

    col->size--; // Réduire la taille logique de la colonne après la suppression
}