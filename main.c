#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"
#include "cdataframe.h"

int main() {
    ENUM_TYPE cdftype[] = {INT, STRING, STRUCTURE,FLOAT};
    CDATAFRAME* dataframe = create_cdataframe(cdftype, 3); //Creates a simple dataframe with three columns.
    display_col_names(dataframe);
    dataframe->head->data = create_column(INT, "toto");
    COLUMN * coltest = dataframe->head->next->data;
    coltest->title = "Randcol";
    COLUMN * value_comparison_test = dataframe->head->data;
    dataframe->tail->data = create_column(FLOAT, "titi");
    COLUMN * value_comparison_test2 = dataframe->tail->data;
    dataframe->head->next->next->data = create_column(STRUCTURE, "Students");
    COLUMN* struct_management = dataframe->head->next->next->data;
    int randomval = 1;
    insert_value(coltest, &randomval);
    char* randstring = "toctoc";
    printf("\t %s", randstring);
    insert_value(coltest, randstring); //Creates two columns and fills one with a random value.
    printf("\nValue of first col node : %s", coltest->data->data.string_value);
    printf("\nValue of second col node : %s", coltest->data->next->data.string_value); //Prints them.
    insert_value(value_comparison_test, &randomval); // Sets up the numerical columns to test the comparison functions.
    randomval++;
    insert_value(value_comparison_test, &randomval);
    randomval++;
    insert_value(value_comparison_test, &randomval);
    float randomval2 = 0;
    insert_value(value_comparison_test2, &randomval2);
    randomval2++;
    insert_value(value_comparison_test2, &randomval2);
    randomval2++;
    insert_value(value_comparison_test2, &randomval2);
    cells_inferior_x(dataframe, 2.0);
    cells_superior_x(dataframe, 0);
    cells_equal_x(dataframe, 2.0);
    printf("\nPrinting test column to see if correct.");
    print_col(value_comparison_test);
    printf("\n---------");
    print_col(value_comparison_test2);
    rows_cols(dataframe);
    display_col_names(dataframe);
    printf("\n Filling -------");
    add_row(dataframe, 1);
    add_row(dataframe, 1);
    add_row(dataframe, 0);
    print_col(coltest);
    print_col(value_comparison_test);
    print_col(struct_management);
    print_col(value_comparison_test2); //After hard fill  and user fill function develop test with dataframe of all types
    printf("\nDoes toctoc exist : %d", does_value_exist(dataframe, randstring, STRING));
    printf("\nDeleting entire Cdataframe\n------");
    delete_cdataframe(&dataframe);
    return 0;
}
