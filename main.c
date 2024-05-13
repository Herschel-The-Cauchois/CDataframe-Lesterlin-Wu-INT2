#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"
#include "cdataframe.h"

int main() {
    ENUM_TYPE cdftype[] = {INT, STRING, FLOAT};
    CDATAFRAME* dataframe = create_cdataframe(cdftype, 3); //Creates a simple dataframe with three columns.
    dataframe->head->data = create_column(INT, "toto");
    COLUMN * coltest = dataframe->head->next->data;
    coltest->title = "Randcol";
    COLUMN * value_comparison_test = dataframe->head->data;
    dataframe->tail->data = create_column(FLOAT, "titi");
    COLUMN * value_comparison_test2 = dataframe->tail->data;
    printf("Am i failing here ?");
    int randomval = 1;
    insert_value(coltest, &randomval);
    insert_value(coltest, &randomval); //Creates two columns and fills one with a random value.
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
    printf("\n%s", coltest->title);
    //delete_column(dataframe, "Randcol"); //Deletes randcol column.
    printf("\n%s", coltest->title);  //Tries to print the title of the deleted column, which should yield nonsense.
    printf("\nTest");
    return 0;
}
