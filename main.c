#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"
#include "cdataframe.h"

int main() {
    ENUM_TYPE cdftype[] = {INT, STRING};
    CDATAFRAME* dataframe = create_cdataframe(cdftype, 2); //Creates a simple dataframe with two columns.
    dataframe->head->data = create_column(INT, "toto");
    COLUMN * coltest = dataframe->tail->data;
    coltest->title = "Randcol";
    int randomval = 1;
    insert_value(coltest, &randomval);
    insert_value(coltest, &randomval); //Creates two columns and fills one with a random value.
    printf("\nValue of first col node : %s", coltest->data->data.string_value);
    printf("\nValue of second col node : %s", coltest->data->next->data.string_value); //Prints them.
    printf("\n%s", coltest->title);
    delete_column(dataframe, "Randcol"); //Deletes randcol column.
    printf("\n%s", coltest->title);  //Tries to print the title of the deleted column, which should yield nonsense.
    printf("\nTest");
    return 0;
}
