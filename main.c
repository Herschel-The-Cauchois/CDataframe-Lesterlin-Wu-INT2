#include <stdio.h>
#include "list.h"
#include "column.h"

int main() {
    printf("Hello, World!\n");
    int a = 1;
    COLUMN test1;
    test1.title = "a";
    lnode* test = lst_create_lnode(&test1);
    printf("%s", ((COLUMN*) test->data)->title);
    return 0;
}
