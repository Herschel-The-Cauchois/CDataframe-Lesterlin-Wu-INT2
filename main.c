#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"
#include "cdataframe.h"

int main() {
    ENUM_TYPE cdftype[] = {INT, STRING};
    CDATAFRAME* dataframe = create_cdataframe(cdftype, 2);
    COLUMN * coltest = dataframe->tail->data;
    int randomval = 1;
    insert_value(coltest, &randomval);
    insert_value(coltest, &randomval);
    printf("\nValue of first col node : %s", coltest->data->data.string_value);
    printf("\nValue of second col node : %s", coltest->data->next->data.string_value);
    return 0;
}
