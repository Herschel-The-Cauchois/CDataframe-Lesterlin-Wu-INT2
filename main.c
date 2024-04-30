#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"

int main() {
    printf("Hello, World!\n");
    COLUMN* test1, *test4;
    test1 = create_column(UINT, "test");
    test4 = create_column(STRING, "test4");
    printf("%s", test1->title);
    int test2 = 1;
    char* test3 = "aa";
    char* test5 = "ttttt";
    //Hard fills test1 numerical column
    insert_value(test1, &test2);
    test2++;
    insert_value(test1, &test2);
    test2++;
    insert_value(test1, &test2);
    test2++;
    insert_value(test1, &test2);
    printf("\n%d", test1->data->data.int_value); // Looks up first value
    //Fills up test4 column of strings.
    insert_value(test4, test3);
    printf("\n%s", test4->data->data.string_value);
    insert_value(test4, test5);
    printf("\n%s", test4->data->next->data.string_value);
    free_value(test4, 2); //Frees a string of text4 column
    printf("\n-------- COLPRINT TEST -------");
    print_col(test1);
    printf("\n--- [COUNTER COLPRINT TEST] ----");
    printf("\n%d", test1->data->data.int_value);
    DATARRAY* temp = test1->data;
    printf("\n%d", temp->data.int_value);
    while (temp != NULL) {
        printf("\n%d", temp->data.int_value);
        temp = temp->next;
    }
    return 0;
}
