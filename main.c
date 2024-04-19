#include <stdio.h>
#include "list.h"
#include "column.h"

int main() {
    printf("Hello, World!\n");
    COLUMN* test1, *test4;
    test1 = create_column(INT, "test");
    test4 = create_column(STRING, "test4");
    printf("%s", test1->title);
    int test2 = 1;
    char* test3 = "aa";
    char* test5 = "ttttt";
    insert_value(test1, &test2);
    printf("\n%d", test1->data->data.int_value);
    insert_value(test4, test3);
    printf("\n%s", test4->data->data.string_value);
    insert_value(test4, test5);
    printf("\n%s", test4->data->next->data.string_value);
    return 0;
}
