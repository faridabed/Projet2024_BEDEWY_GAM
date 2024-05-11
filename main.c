#include "column.h"
#include "cdataframe.h"
#include <stdio.h>

int main() {

    menu();
    COLUMN* mycol = create_column(CHAR, "Ma Colonne");
    insert_value(mycol, "A");
    insert_value(mycol, "B");
    insert_value(mycol, "C");

    print_col(mycol);

    delete_column(&mycol);

    CDATAFRAME* df = create_cdataframe();
    COLUMN* col1 = create_column(CHAR, "Colonne 1");
    COLUMN* col2 = create_column(INT, "Colonne 2");

    insert_value(col1, "A");
    insert_value(col1, "B");
    insert_value(col2, (void*)&(int){100});
    insert_value(col2, (void*)&(int){200});

    add_column(df, col1);
    add_column(df, col2);

    display_cdataframe(df);

    delete_cdataframe(&df);


    return 0;
}

