//
// Created by fbedewy on 19/05/2024.
//

#include "cdataframe.h"

void add_row_to_dataframe(CDATAFRAME* df) {
    if (df == NULL) {
        printf("Erreur: DataFrame non initialise.\n");
        return;
    }

    if (df->size == 0) {
        printf("Erreur: Aucune colonne n'est presente dans le DataFrame. Veuillez d'abord creer une colonne.\n");
        return;
    }

    void* values[df->size]; // Tableau pour stocker les adresses des valeurs à insérer


    for (unsigned int i = 0; i < df->size; i++) {
        COLUMN* col = df->columns[i];
        printf("Inserer une valeur pour la colonne '%s' (Type %d):\n", col->title, col->column_type);

        switch (col->column_type) {
            case INT: {
                int* value = (int*) malloc(sizeof(int));
                printf("Entrez une valeur entiere: ");
                scanf("%d", value);
                values[i] = value;
                break;
            }
            case FLOAT: {
                float* value = (float*) malloc(sizeof(float));
                printf("Entrez une valeur flottante: ");
                scanf("%f", value);
                values[i] = value;
                break;
            }
            case CHAR: {
                char* value = (char*) malloc(sizeof(char));
                printf("Entrez un caractere: ");
                scanf(" %c", value);  // L'espace avant %c consomme le newline
                values[i] = value;
                break;
            }
            case STRING: {
                char* value = (char*) malloc(100 * sizeof(char));  // Taille fixe pour l'exemple
                printf("Entrez une chaine de caracteres: ");
                scanf(" %99s", value);  // Protège contre les débordements de tampon
                values[i] = value;
                break;
            }
            default:
                printf("Type non pris en charge pour l'ajout de valeurs.\n");
                values[i] = NULL;
        }
    }


    for (unsigned int i = 0; i < df->size; i++) {
        if (values[i] != NULL) {
            insert_value(df->columns[i], values[i]);
            free(values[i]);  // Libérer la mémoire allouée pour chaque valeur
        }
    }
}

void insert_value_into_column(COLUMN* col) {
    if (col == NULL) {
        printf("Erreur : Aucune colonne selectionnee.\n");
        return;
    }

    printf("Inserer une valeur dans la colonne de type '%s'.\n", col->title);

    switch (col->column_type) {
        case INT: {
            int value;
            printf("Entrez une valeur entiere : ");
            scanf("%d", &value);
            insert_value(col, &value);
            break;
        }
        case FLOAT: {
            float value;
            printf("Entrez une valeur flottante : ");
            scanf("%f", &value);
            insert_value(col, &value);
            break;
        }
        case CHAR: {
            char value;
            printf("Entrez un caractere : ");
            scanf(" %c", &value);
            insert_value(col, &value);
            break;
        }
        case STRING: {
            char value[100];
            printf("Entrez une chaine de caracteres : ");
            scanf(" %99s", value);
            insert_value(col, value);
            break;
        }
        default:
            printf("Type non supporte pour l'insertion.\n");
    }
}

void column_menu(CDATAFRAME* df) {
    int choice;
    while (1) {
        printf("\nMenu Colonnes:\n");
        printf("1. Ajouter une colonne\n");
        printf("2. Inserer des valeurs dans une colonne\n");
        printf("3. Supprimer une colonne\n");
        printf("4. Renommer une colonne\n");
        printf("5. Retour\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        unsigned int index;
        char title[256];
        COLUMN* col;
        char new_name[256];

        switch (choice) {
            case 1:
                printf("Entrez le type de colonne (0: INT, 1: CHAR, 2: FLOAT, 3: DOUBLE, 4: STRING): ");
                int col_type;
                scanf("%d", &col_type);
                printf("Entrez le titre de la colonne: ");
                scanf("%s", title);
                col = create_column((ENUM_TYPE)col_type, title);
                if (add_column(df, col)) {
                    printf("Colonne ajoutee avec succes.\n");
                } else {
                    printf("Erreur lors de l'ajout de la colonne.\n");
                }
                break;
            case 2:
                insert_value_into_column(col);
                break;
            case 3:
                printf("Entrez l'index de la colonne a supprimer: ");
                scanf("%u", &index);
                remove_column(df, index);
                printf("Colonne supprimee.\n");
                break;
            case 4:
                printf("Entrez l'index de la colonne a renommer: ");
                scanf("%u", &index);
                printf("Entrez le nouveau nom de la colonne: ");
                scanf("%s", new_name);
                rename_column(df, index, new_name);
                printf("Colonne renommee.\n");
                break;
            case 5:
                return;
            default:
                printf("Choix invalide.\n");
        }
    }
}
// fonction menu
void row_menu(CDATAFRAME* df) {
    int choice;
    while (1) {
        printf("\nMenu Lignes:\n");
        printf("1. Ajouter une ligne\n");
        printf("2. Supprimer une ligne\n");
        printf("3. Retour\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        void** row_data;
        unsigned int row_index;

        switch (choice) {
            case 1:
                row_data = malloc(df->size * sizeof(void*));
                for (unsigned int i = 0; i < df->size; i++) {
                    printf("Entrez la valeur pour la colonne %s: ", df->columns[i]->title);
                    switch (df->columns[i]->column_type) {
                        case INT:
                            row_data[i] = malloc(sizeof(int));
                            scanf("%d", (int*)row_data[i]);
                            break;
                        case CHAR:
                            row_data[i] = malloc(sizeof(char));
                            scanf(" %c", (char*)row_data[i]);
                            break;
                        case FLOAT:
                            row_data[i] = malloc(sizeof(float));
                            scanf("%f", (float*)row_data[i]);
                            break;
                        case DOUBLE:
                            row_data[i] = malloc(sizeof(double));
                            scanf("%lf", (double*)row_data[i]);
                            break;
                        case STRING:
                            row_data[i] = malloc(256 * sizeof(char));
                            scanf("%s", (char*)row_data[i]);
                            break;
                    }
                }
                if (add_row(df, row_data)) {
                    printf("Ligne ajoutee avec succes.\n");
                } else {
                    printf("Erreur lors de l'ajout de la ligne.\n");
                }
                for (unsigned int i = 0; i < df->size; i++) {
                    free(row_data[i]);
                }
                free(row_data);
                break;
            case 2:
                printf("Entrez l'index de la ligne a supprimer: ");
                scanf("%u", &row_index);
                remove_row(df, row_index);
                printf("Ligne supprimee.\n");
                break;
            case 3:
                return;
            default:
                printf("Choix invalide.\n");
        }
    }
}

void display_menu(CDATAFRAME* df) {
    int choice;
    while (1) {
        printf("\nMenu Affichage:\n");
        printf("1. Afficher le DataFrame complet\n");
        printf("2. Afficher une partie du DataFrame\n");
        printf("3. Afficher les noms des colonnes\n");
        printf("4. Retour\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        unsigned int start_row, num_rows;

        switch (choice) {
            case 1:
                display_cdataframe(df);
                break;
            case 2:
                printf("Entrez la ligne de depart: ");
                scanf("%u", &start_row);
                printf("Entrez le nombre de lignes a afficher: ");
                scanf("%u", &num_rows);
                display_partial_dataframe(df, start_row, num_rows);
                break;
            case 3:
                display_column_names(df);
                break;
            case 4:
                return;
            default:
                printf("Choix invalide.\n");
        }
    }
}



void menu() {
    CDATAFRAME* df = create_cdataframe();
    int choice;
    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Gerer les colonnes\n");
        printf("2. Gerer les lignes\n");
        printf("3. Remplir en dur \n");
        printf("4. Remplacer une valeur de cellule\n");
        printf("5. Afficher le DataFrame\n");
        printf("6. Trouver une valeur\n");
        printf("7. Compter les lignes\n");
        printf("8. Compter les colonnes\n");
        printf("9. Compter les cellules repondant a une condition\n");
        printf("10. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        int int_value;
        void* value;

        switch (choice) {
            case 1:
                column_menu(df);
                break;
            case 2:
                row_menu(df);
                break;
            case 3:
                fill_cdataframe_hardcoded(df);
                break;
                int col_index, row_index;
            case 4:
                printf("Choisisez l'index de la colonne et de la ligne que vous voulez remplacer: ");
                scanf(" %d %d ", &col_index, &row_index);
                switch (df->columns[col_index]->column_type) {
                    case INT: {
                        int new_value;
                        printf("Entrez une valeur entiere : ");
                        scanf("%d", &new_value);
                        demo_replace_value(df, col_index,row_index, &new_value);
                        break;
                    }
                    case FLOAT: {
                        float new_value;
                        printf("Entrez une valeur flottante : ");
                        scanf("%f", &new_value);
                        demo_replace_value(df, col_index,row_index, &new_value);
                        break;
                    }
                    case CHAR: {
                        char new_value;
                        printf("Entrez un caractere : ");
                        scanf(" %c", &new_value);
                        demo_replace_value(df, col_index,row_index, &new_value);
                        break;
                    }
                    case STRING: {
                        char new_value[100];
                        printf("Entrez une chaine de caracteres : ");
                        scanf(" %99s", &new_value);
                        demo_replace_value(df, col_index,row_index, &new_value);
                        break;
                    }
                    default:
                        printf("Type non supporte pour l'insertion.\n");
                }
            case 5:
                display_menu(df);
                break;
            case 6:
                printf("Entrez la valeur a trouver (seulement pour les entiers): ");
                scanf("%d", &int_value);
                value = &int_value;
                if (find_value(df, value)) {
                    printf("Valeur trouvee.\n");
                } else {
                    printf("Valeur non trouvee.\n");
                }
                break;
            case 7:
                printf("Nombre de lignes: %u\n", count_rows(df));
                break;
            case 8:
                printf("Nombre de colonnes: %u\n", count_columns(df));
                break;
            case 9:
                printf("Entrez la valeur a comparer: ");
                scanf("%d", &int_value);
                //printf("Nombre de cellules répondant à la condition: %u\n", count_cells_meeting_condition(df, int_value, ?(int a, int b)  { return a == b; }));
                printf("Bientot disponible\n");
                break;
            case 10:
                delete_cdataframe(&df);
                return;
            default:
                printf("Choix invalide.\n");
        }
    }
}