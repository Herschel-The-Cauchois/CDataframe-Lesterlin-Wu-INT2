#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"
#include "cdataframe.h"

int main() {
    ENUM_TYPE cdftype[] = {INT, STRING, STRUCTURE,FLOAT};
    CDATAFRAME* dataframe = create_cdataframe(cdftype, 4); //Creates a simple dataframe with four columns.
    display_col_names(dataframe);
    COLUMN * coltest = dataframe->head->next->data;
    rename_col(dataframe, "Sans nom 1", "toto");
    rename_col(dataframe, "Sans nom 2", "Randcol");
    rename_col(dataframe, "Sans nom 3", "Students");
    rename_col(dataframe, "Sans nom 4", "titi");
    COLUMN * value_comparison_test = dataframe->head->data;
    COLUMN * value_comparison_test2 = dataframe->tail->data;
    COLUMN* struct_management = dataframe->head->next->next->data;
    fill_cdataframe(dataframe);
    cells_inferior_x(dataframe, 2.0);
    cells_superior_x(dataframe, 0);
    cells_equal_x(dataframe, 2.0);
    rows_cols(dataframe);
    display_col_names(dataframe);
    printf("\n Filling -------");
    add_row(dataframe, 1);
    printf("\nMemory be working ???");
    add_row(dataframe, 1);
    printf("\nMemory be working ???");
    delete_row(dataframe, 0);
    print_col(coltest);
    print_col(value_comparison_test);
    print_col(struct_management);
    print_col(value_comparison_test2); //After hard fill  and user fill function develop test with dataframe of all types
    STUDENT me;
    me.id = 2;
    me.average = 1;
    printf("\nDoes student 2 exist : %d", does_value_exist(dataframe, &me, STRUCTURE));
    add_col(dataframe);
    add_row(dataframe, 1);
    print_col(dataframe->tail->data);
    print_col(struct_management);
    access_replace_value(dataframe, 2, 3);
    display_cdataframe(dataframe);
    display_cdataframe_col_limited(dataframe, 1);
    display_cdataframe_row_limited(dataframe, 2);
    printf("\nDeleting entire Cdataframe\n------");
    delete_cdataframe(&dataframe);
    return 0;
}
