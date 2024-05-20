#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "cdataframe.h"
//Improvement idea for long csv file management : like in complexity exercise on fibonacci, create SLL of dataframes
//containing successive parts of the csv table. To not bloat memory, when looked through a dataframe moves it to the
//head, removes predecessor and add the next bloc of csv lines as a new dataframe as successor.

//CDataframe creation function
CDATAFRAME* create_cdataframe(ENUM_TYPE *cdftype, int size) {
    CDATAFRAME* dataframe = (CDATAFRAME*) malloc(sizeof(CDATAFRAME)); //Initializes the dataframe.
    lnode* start = (lnode*) malloc(sizeof(lnode)); //Creates its head node.
    dataframe->head = start; //Assigns it to the head member of the dataframe.
    if (cdftype == NULL || size < 1) { //Check if the array of types is not empty or if the size is not strictly positive.
        printf("\nNo types given or size too small, empty dataframe returned.");
        return dataframe;
    }
    int typenb = 0;
    while (cdftype[typenb] != NULL) {
        typenb++;
    }
    if (typenb < size || typenb < 1) {
        //Previous loop counts the number of element in the type array and compares it to the size parameter.
        //If size is too large, or typenb isn't stricly positive, also returns an empty dataframe.
        printf("Not enough types given, empty dataframe returned.");
        return dataframe;
    }
    //If both cases aren't true, initializes the head node's column.
    start->data = create_column(cdftype[0], "Sans nom 1");
    start->prev = NULL;
    lnode* temp = start;
    //after that, for all remaining types in the cdftype array:
    for (int i = 1; i < size; i++) {
        lnode* new = (lnode*) malloc(sizeof(lnode));
        new->next = NULL; //Very important, sets the successor of the new node to NULL.
        temp->next = new; //Initialises a new lnode to put to the succession of the previous, starting from
        //the head node.
        new->prev = temp; //puts temp as the predecessor of new.
        char* coltitle = (char*) malloc(20*sizeof(char));
        snprintf(coltitle, 20, "Sans nom %d", i+1); //Formats a default title string for each column.
        COLUMN* new_col = create_column(cdftype[i], coltitle);
        new->data = new_col; //Initializes new column and puts it in the lnode's data.
        temp = temp->next; //Goes to next lnode.
    }
    dataframe->tail = temp; //Sets tail of the dataframe as the last lnode put in temp.
    dataframe->tail->next = NULL;
    return dataframe;
}

void delete_column(CDATAFRAME *cdf, char *col_name) {
    lnode* temp = cdf->head; //Creates temporary pointer that points to the start node.
    COLUMN* col = NULL;
    lnode* col_node;
    while (temp != NULL) {
        if (temp->data != NULL && !strcmp(((COLUMN*) temp->data)->title,col_name)) {
            col = (COLUMN *) temp->data;  //The col pointer will then each time point at the column data of the node.
            col_node = temp;
        }
        temp = temp->next;
    }
    if (col == NULL) {
        //If the column wasn't found, ends the function.
        printf("\nNot found");
        return;
    }
    int flag = 0;
    while (flag == 0) {
        //Until the free_value functions returns a 1 that indicates that the second element of the SLL is freed, loops.
        flag = free_value(col, 1);
    }
    free_value(col, 0); //Frees the head of the column.
    free(col);  //Frees the data attribute of the node itself.
    lst_delete_lnode(cdf, col_node); //Frees the now useless node of the deleted column.
    printf("\nColumn deleted !");
}

void delete_cdataframe(CDATAFRAME **cdf) {
    if (*cdf == NULL) {
        return;
    }
    while ((*cdf)->head != NULL) {
        char* col_title = ((COLUMN*) (*cdf)->tail->data)->title;
        delete_column(*cdf, col_title);
    }
    free(*cdf);
}

void fill_cdataframe(CDATAFRAME *cdf) {
    unsigned int hard = 2;
    unsigned long long int size = 0;
    while (hard > 1) {
        printf("\nWould you like to hardfill (1) or write by yourself data (0) ? Enter preferred option : ");
        scanf("%u", &hard);
    }
    while (size == 0) {
        printf("\nEnter the desired size of your filling : ");
        scanf("%llu", &size);
    }
    for (unsigned long long int i = 0; i < size; i++) {
        add_row(cdf, hard);
    }
}

void display_cdataframe(CDATAFRAME *cdf) {
    //Takes the SLL and runs through it to print each of its columns.
    lnode* temp = cdf->head;
    while (temp != NULL) {
        print_col(temp->data);
        temp = temp->next;
    }
}

void display_cdataframe_row_limited(CDATAFRAME *cdf, unsigned long long int limit) {
    lnode* temp = cdf->head; //Stores the head of the dataframe's SLL here.
    while (temp != NULL) {
        DATARRAY* temp2 = ((COLUMN*) temp->data)->data; //Stores the column's data SLL
        int iterator = 0;
        char* buffer = (char*) malloc(64*sizeof(char));
        printf("\n%s\n-------", ((COLUMN*) temp->data)->title);
        do {
            //For each node encountered, proceeds to convert it into a string, and then print it to the side of its index.
            display_converter(((COLUMN*) temp->data), iterator, buffer, 64);
            printf("\n[%d] %s", iterator, buffer); //Prints the index of an element in the list as well as the data itself.
            temp2 = temp2->next; //Moves to the next node and increases iterator that represents the node's index.
            iterator++;
        } while (temp2 != NULL && iterator < limit); //Continues until the end of the list is met or the iterator passes the limit.
        temp = temp->next;
    }
}

void display_cdataframe_col_limited(CDATAFRAME *cdf, int limit) {
    //Same principle as display_cdataframe, except that a counter will trigger the end of the while loop if the limit is passed.
    lnode* temp = cdf->head;
    int counter = 0;
    while (temp != NULL && counter < limit) {
        print_col(temp->data);
        counter++;
        temp = temp->next;
    }
}

int add_row(CDATAFRAME *cdf, int hard) {
    lnode* temp = cdf->head; //Puts in a pointer the head of the list of columns.
    while (temp != NULL) { //Repeats until all columns got a new node in them.
        int* randominator = (int*) malloc(sizeof(int)); //Uses an empty variable to generate random input for hard filling.
        srand(time(NULL));
        *randominator = rand();
        COL_TYPE new_data; //For user input filling, creates a variable that can hold all the datatypes the dataframe can handle.
        switch (((COLUMN*) temp->data)->column_type) {

            case NULLVAL: //If the column doesn't have a type, does not bother to try filling it.
                return 1;
            case UINT:
                if (hard) { //If the hard boolean value is true, proceeds to the allocation of a random number.
                    new_data.uint_value = (unsigned int) *randominator;
                } else { //Else, asks the user to enter a value.
                    printf("\nEnter an unsigned integer : ");
                    scanf("%u", &(new_data.uint_value));
                }
                insert_value(temp->data, &new_data); //Inserts it with the column function inside.
                break; //Repeat for all other cases.
            case INT:
                if (hard) {
                    new_data.int_value = (int) *randominator;
                } else {
                    printf("\nEnter an integer : ");
                    scanf("%d", &(new_data.int_value));
                }
                insert_value(temp->data, &new_data);
                break;
            case CHAR:
                if (hard) {
                    new_data.char_value = (char) *randominator;
                } else {
                    printf("\nEnter a character : ");
                    scanf("%c", &(new_data.char_value));
                    scanf("%c", &(new_data.char_value));
                }
                insert_value(temp->data, &new_data);
                break;
            case FLOAT:
                if (hard) {
                    new_data.float_value = (float) *randominator;
                } else {
                    printf("\nEnter a float : ");
                    scanf("%f", &(new_data.float_value));
                }
                insert_value(temp->data, &new_data);
                break;
            case DOUBLE:
                if (hard) {
                    new_data.double_value = (double) *randominator;
                } else {
                    printf("\nEnter a double float : ");
                    scanf("%lf", &(new_data.double_value));
                }
                insert_value(temp->data, &new_data);
                break;
            case STRING:
                if (hard) {
                    new_data.string_value = (char*) malloc(30*sizeof(char));
                    new_data.string_value = (char*) randominator; //If in hard filling mode, produces a random string.
                } else {
                    printf("\nEnter size of the string : ");
                    char* temp2 = (char*) malloc(256*sizeof(char));
                    unsigned int size = -1; //This will be converted into a huge value to trick the program to trigger the while loop to avoid skipping the size entering phase.
                    while (size > 256) {
                        scanf("%d", &size); //Lets the user enter a personalized string size for flexible memory management.
                    }
                    new_data.string_value = (char*) malloc((size+1)*sizeof(char)); //Test string management with this
                    printf("\nEnter a string (Entering a longer string than expected will cut it) : ");
                    gets(temp2); //Repeats the gets instruction to avoid the backspace filling the buffer
                    gets(temp2); //And skipping the user input phase.
                    snprintf(new_data.string_value, size+1, "%s", temp2);
                    //Since this member is a pointer, the string member is passed directly.
                }
                insert_value(temp->data, new_data.string_value);
                break;
            case STRUCTURE:
                if (hard) {
                    ((STUDENT*) new_data.struct_value)->id = (int) *randominator;
                    ((STUDENT*) new_data.struct_value)->average = (float) abs(*randominator);
                } else {
                    printf("\nEnter Student ID (integer) : ");
                    scanf("%d", &((STUDENT*) new_data.struct_value)->id);
                    printf("\nEnter Student average grade : ");
                    scanf("%f", &((STUDENT*) new_data.struct_value)->average);
                }
                insert_value(temp->data, new_data.struct_value);
                break;
        }
        temp = temp->next;
    }
    return 0;
}

void delete_row(CDATAFRAME *cdf, unsigned long long int i) {
    lnode* temp = cdf->head; //Creates a pointer at the head of the list of columns.
    while (temp != NULL) {
        free_value(temp->data, i); //Uses the free value function at index i on all columns.
        temp = temp->next;
    }
}

int add_col(CDATAFRAME *cdf) {
    lnode* tail = cdf->tail; //Creates a pointer at the tail of the list of columns.
    lnode* new = (lnode*) malloc(sizeof(lnode));
    new->prev = tail;
    new->next = NULL;  //Initializes the future new lnode to preserve the logic of the list.
    printf("\nEnter a title for the column : ");
    char* title = (char*) malloc(32*sizeof(char));
    gets(title); //Same trick to avoid buffer backspace filling.
    gets(title);
    int type = 1;
    while (type < 2 || type > 8) { //Secures input to obtain a type supported by the program.
        printf("\nChoose a type for the column, from 2 to 8 (UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE) : ");
        scanf("%d", &type);
    }
    new->data = create_column(type, title); //Creates the column and puts the new node-column at the tail of the list.
    tail->next = new;
    cdf->tail = new;
    return 0;
}

int rename_col(CDATAFRAME *cdf, char* column, char* new_name) {
    lnode* temp = cdf->head; //Creates temporary pointer that points to the start node.
    COLUMN* col = NULL;
    lnode* col_node;
    while (temp != NULL) {
        if (temp->data != NULL && !strcmp(((COLUMN*) temp->data)->title, column)) {
            col = (COLUMN *) temp->data;  //The col pointer will then each time point at the column data of the node.
            col_node = temp;
            printf("\n%u", col->column_type);  //Prints the column type if it finds it.
        }
        temp = temp->next;
    }
    if (col == NULL) {
        //If the column wasn't found, ends the function.
        printf("\nNot found");
        return 0;
    }
    ((COLUMN*) col_node->data)->title = new_name;
    return 1;
}

int does_value_exist(CDATAFRAME *cdf, void *value, ENUM_TYPE datatype) {
    lnode* temp = cdf->head; //Stores the head of the list of columns.
    switch (datatype) {

        case NULLVAL:
            return 0; //If the given value doesn't have a type, returns 0.
        case UINT:
            while (temp != NULL) { //Loops through the list of columns.
                if (((COLUMN*) temp->data)->column_type == UINT) { //If the column is of Uint type :
                    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data; //Creates a pointer for the column's head.
                    while (col_explorer != NULL) { //Loops through the column SLL.
                        if (col_explorer->data.uint_value == *((unsigned int*) value)) {
                            //If the value of the member of the union and the variable corresponds, returns 1 (found).
                            return 1;
                        }
                        col_explorer = col_explorer->next;
                    }
                }
                temp = temp->next;
            }
            return 0; //Else returns 0, not found.
        case INT:
            while (temp != NULL) {
                if (((COLUMN*) temp->data)->column_type == INT) {
                    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data;
                    while (col_explorer != NULL) {
                        if (col_explorer->data.int_value == *((int*) value)) {
                            return 1;
                        }
                        col_explorer = col_explorer->next;
                    }
                }
                temp = temp->next;
            }
            return 0;
        case CHAR:
            while (temp != NULL) {
                if (((COLUMN*) temp->data)->column_type == CHAR) {
                    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data;
                    while (col_explorer != NULL) {
                        if (col_explorer->data.char_value == *((char*) value)) {
                            return 1;
                        }
                        col_explorer = col_explorer->next;
                    }
                }
                temp = temp->next;
            }
            return 0;
        case FLOAT:
            while (temp != NULL) {
                if (((COLUMN*) temp->data)->column_type == FLOAT) {
                    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data;
                    while (col_explorer != NULL) {
                        if (col_explorer->data.float_value == *((float*) value)) {
                            return 1;
                        }
                        col_explorer = col_explorer->next;
                    }
                }
                temp = temp->next;
            }
            return 0;
        case DOUBLE:
            while (temp != NULL) {
                if (((COLUMN*) temp->data)->column_type == DOUBLE) {
                    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data;
                    while (col_explorer != NULL) {
                        if (col_explorer->data.double_value == *((double*) value)) {
                            return 1;
                        }
                        col_explorer = col_explorer->next;
                    }
                }
                temp = temp->next;
            }
            return 0;
        case STRING:
            while (temp != NULL) {
                if (((COLUMN*) temp->data)->column_type == STRING) {
                    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data;
                    while (col_explorer != NULL) {
                        if (strcmp(col_explorer->data.string_value, (char*) value) == 0) {
                            return 1;
                        }
                        col_explorer = col_explorer->next;
                    }
                }
                temp = temp->next;
            }
            return 0;
        case STRUCTURE:
            while (temp != NULL) {
                if (((COLUMN*) temp->data)->column_type == STRUCTURE) {
                    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data;
                    while (col_explorer != NULL) {
                        if (((STUDENT*) col_explorer->data.struct_value)->id == ((STUDENT*) value)->id && ((STUDENT*) col_explorer->data.struct_value)->average == ((STUDENT*) value)->average) {
                            return 1;
                        }
                        col_explorer = col_explorer->next;
                    }
                }
                temp = temp->next;
            }
        default:
            return 0;
    }
}

int access_replace_value(CDATAFRAME *cdf, unsigned long long int row, unsigned long long int col) {
    lnode* temp = cdf->head; //Points towards the head of the linked list.
    unsigned long long int row_index = 0, col_index = 0; //Sets up local variables that will be incremented as we loop through the SLLs.
    while (temp != NULL && col != col_index) { //Looks for the right column, if ends up at the end of the dataframe will stop the function.
        col_index++;
        temp = temp->next;
    }
    if (temp == NULL) {
        return 1;
    }
    DATARRAY* temp2 = ((COLUMN*) temp->data)->data;
    while (temp2 != NULL && row != row_index) { //Does the same for the rows.
        row_index++;
        temp2 = temp2->next;
    }
    if (temp2 == NULL) {
        return 1;
    }
    char* display_buffer = (char*) malloc(32*sizeof(char));
    display_converter(temp->data, row_index, display_buffer, 32);
    printf("\nReached value : %s", display_buffer); //Displays the reached values and proposes to change it.
    unsigned int yes_or_no = 2;
    while (yes_or_no > 1) {
        printf("\nWould you like to replace it ? (Y : 1/N : 0) : ");
        scanf("%u", &yes_or_no);
    }
    if (!yes_or_no) {
        return 0; //If no, ends up successfully the function.
    } else {
        COL_TYPE new_data; //For user input filling, creates a variable that can hold all the datatypes the dataframe can handle.
        switch (((COLUMN*) temp->data)->column_type) {

            case NULLVAL: //If the column doesn't have a type, does not bother to try filling it.
                return 1;
            case UINT:
                printf("\nEnter an unsigned integer : ");
                scanf("%u", &(new_data.uint_value));
                temp2->data.uint_value = new_data.uint_value; //Replace the old value with the new value.
                break; //Repeat for all other cases.
            case INT:
                printf("\nEnter an integer : ");
                scanf("%d", &(new_data.int_value));
                temp2->data.int_value = new_data.int_value;
                break;
            case CHAR:
                printf("\nEnter a character : ");
                scanf("%c", &(new_data.char_value));
                scanf("%c", &(new_data.char_value));
                temp2->data.char_value = new_data.char_value;
                break;
            case FLOAT:
                printf("\nEnter a float : ");
                scanf("%f", &(new_data.float_value));
                temp2->data.float_value = new_data.float_value;
                break;
            case DOUBLE:
                printf("\nEnter a double float : ");
                scanf("%lf", &(new_data.double_value));
                temp2->data.double_value = new_data.double_value;
                break;
            case STRING:
                printf("\nEnter size of the string : ");
                char* temp3 = (char*) malloc(256*sizeof(char));
                unsigned int size = -1; //This will be converted into a huge value to trick the program to trigger the while loop to avoid skipping the size entering phase.
                while (size > 256) {
                    scanf("%d", &size); //Lets the user enter a personalized string size for flexible memory management.
                }
                new_data.string_value = (char*) malloc((size+1)*sizeof(char)); //Test string management with this
                printf("\nEnter a string (Entering a longer string than expected will cut it) : ");
                gets(temp3); //Repeats the gets instruction to avoid the backspace filling the buffer
                gets(temp3); //And skipping the user input phase.
                snprintf(new_data.string_value, size+1, "%s", temp3);
                //Since this member is a pointer, the string member is passed directly.
                temp2->data.string_value = new_data.string_value;
                break;
            case STRUCTURE:
                new_data.struct_value = (STUDENT*) malloc(sizeof(STUDENT));
                printf("\nEnter Student ID (integer) : ");
                scanf("%d", &((STUDENT*) new_data.struct_value)->id);
                printf("\nEnter Student average grade : ");
                scanf("%f", &((STUDENT*) new_data.struct_value)->average);
                temp2->data.struct_value = new_data.struct_value;
                break;
        }
        return 0;
    }
}

void display_col_names(CDATAFRAME *cdf) {
    lnode* temp = cdf->head; //Stores the head of the list of columns.
    while (temp != NULL) {
        //As long as we haven't hit an empty successor, prints the title of the column.
        printf("\n%s", ((COLUMN*) temp->data)->title);
        temp = temp->next;
    }
}

void rows_cols(CDATAFRAME *cdf) {
    lnode* temp = cdf->head; //Creates a temporary pointer with the head of the list.
    int cols = 0; //Creates two variables to store the number of columns and rows.
    unsigned long long int rows = 0;
    while (temp != NULL) {
        cols++; //Counts column by looping through the cdataframe list.
        temp = temp->next;
    }
    temp = cdf->tail;
    DATARRAY* col_explorer = ((COLUMN*) temp->data)->data; //Retrieves a pointer to the last column's content.
    while (col_explorer != NULL) {
        rows++;  //Loops through the said column and increments each time it encounters a non-empty node.
        col_explorer = col_explorer->next;
    }
    printf("\nThis Dataframe has %d columns and %llu rows.", cols, rows);
}

void cells_equal_x(CDATAFRAME *cdf, double x) {
    lnode* temp = cdf->head;
    if (cdf->head == NULL) {
        //If the cdataframe is empty, stops the function.
        return;
    }
    while (temp != cdf->tail->next) { //Stops the check when it hits the tail node of the list. A != NULL test provokes Cx05 error.
        if (temp->data != NULL) { //Tests if the column has no empty data.
            if (((COLUMN*) temp->data)->column_type == INT || ((COLUMN*) temp->data)->column_type == FLOAT || ((COLUMN*) temp->data)->column_type == UINT || ((COLUMN*) temp->data)->column_type == DOUBLE) {
                //Verifies if the current column is of numerical type.
                DATARRAY* col_explorer = ((COLUMN*) temp->data)->data; //Creates a new temporary pointer to loop through the column if it is of correct type.
                unsigned long long int i = 0;  // Creates an index variable to display the position of the element found, if equal to x.
                printf("\n%s\n-------", ((COLUMN*) temp->data)->title);  // Starts the display by displaying the title of the column.
                while (col_explorer != NULL) {
                    //Checks all possible numerical types supported by C to compare it to the parameter, as the function loops through the column.
                    if ((double) col_explorer->data.int_value == x) {
                        printf("\n%llu | %d", i, col_explorer->data.int_value);
                    } else if ((double) col_explorer->data.float_value == x) {
                        printf("\n%llu | %.5f", i, col_explorer->data.float_value);
                    } else if ((double) col_explorer->data.double_value == x) {
                        printf("\n%llu | %.5lf", i, col_explorer->data.double_value);
                    } else if ((double) col_explorer->data.uint_value == x) {
                        printf("\n%llu | %u", i, col_explorer->data.uint_value);
                    }
                    i++; //Increments index at the end of the check.
                    col_explorer = col_explorer->next; //Goes to the next node of the column.
                }
            }
        }
        temp = temp->next; //Goes to the next column.
    }
}

void cells_superior_x(CDATAFRAME *cdf, double x) {
    lnode* temp = cdf->head;
    if (cdf->head == NULL) {
        //If the cdataframe is empty, stops the function.
        return;
    }
    while (temp != cdf->tail->next) { //Stops the check when it hits the tail node of the list. A != NULL test provokes Cx05 error.
        if (temp->data != NULL) { //Tests if the column has no empty data.
            if (((COLUMN*) temp->data)->column_type == INT || ((COLUMN*) temp->data)->column_type == FLOAT || ((COLUMN*) temp->data)->column_type == UINT || ((COLUMN*) temp->data)->column_type == DOUBLE) {
                //Verifies if the current column is of numerical type.
                DATARRAY* col_explorer = ((COLUMN*) temp->data)->data; //Creates a new temporary pointer to loop through the column if it is of correct type.
                unsigned long long int i = 0;  // Creates an index variable to display the position of the element found, if equal to x.
                printf("\n%s\n-------", ((COLUMN*) temp->data)->title);  // Starts the display by displaying the title of the column.
                while (col_explorer != NULL) {
                    //Checks all possible numerical types supported by C to compare it to the parameter, as the function loops through the column.
                    if (((COLUMN*) temp->data)->column_type == INT && (float) col_explorer->data.int_value > x) {
                        printf("\n%llu | %d", i, col_explorer->data.int_value);
                    } else if (((COLUMN*) temp->data)->column_type == FLOAT && col_explorer->data.float_value > x) {
                        printf("\n%llu | %.5f", i, col_explorer->data.float_value);
                    } else if (((COLUMN*) temp->data)->column_type == DOUBLE && (float) col_explorer->data.double_value > x) {
                        printf("\n%llu | %.5lf", i, col_explorer->data.double_value);
                    } else if (((COLUMN*) temp->data)->column_type == UINT && (float) col_explorer->data.uint_value > x) {
                        printf("\n%llu | %u", i, col_explorer->data.uint_value);
                    }
                    i++; //Increments index at the end of the check.
                    col_explorer = col_explorer->next; //Goes to the next node of the column.
                }
            }
        }
        temp = temp->next; //Goes to the next column.
    }
}

void cells_inferior_x(CDATAFRAME *cdf, double x) {
    lnode* temp = cdf->head;
    if (cdf->head == NULL) {
        //If the cdataframe is empty, stops the function.
        return;
    }
    while (temp != cdf->tail->next) { //Stops the check when it hits the tail node of the list. A != NULL test provokes Cx05 error.
        if (temp->data != NULL) { //Tests if the column has no empty data.
            if (((COLUMN*) temp->data)->column_type == INT || ((COLUMN*) temp->data)->column_type == FLOAT || ((COLUMN*) temp->data)->column_type == UINT || ((COLUMN*) temp->data)->column_type == DOUBLE) {
                //Verifies if the current column is of numerical type.
                DATARRAY* col_explorer = ((COLUMN*) temp->data)->data; //Creates a new temporary pointer to loop through the column if it is of correct type.
                unsigned long long int i = 0;  // Creates an index variable to display the position of the element found, if equal to x.
                printf("\n%s\n-------", ((COLUMN*) temp->data)->title);  // Starts the display by displaying the title of the column.
                while (col_explorer != NULL) {
                    //Checks all possible numerical types supported by C to compare it to the parameter, as the function loops through the column.
                    if (((COLUMN*) temp->data)->column_type == INT && (float) col_explorer->data.int_value < x) {
                        printf("\n%llu | %d", i, col_explorer->data.int_value);
                    } else if (((COLUMN*) temp->data)->column_type == FLOAT && col_explorer->data.float_value < x) {
                        printf("\n%llu | %.5f", i, col_explorer->data.float_value);
                    } else if (((COLUMN*) temp->data)->column_type == DOUBLE && (float) col_explorer->data.double_value < x) {
                        printf("\n%llu | %.5lf", i, col_explorer->data.double_value);
                    } else if (((COLUMN*) temp->data)->column_type == UINT && (float) col_explorer->data.uint_value < x) {
                        printf("\n%llu | %u", i, col_explorer->data.uint_value);
                    }
                    i++; //Increments index at the end of the check.
                    col_explorer = col_explorer->next; //Goes to the next node of the column.
                }
            }
        }
        temp = temp->next; //Goes to the next column.
    }
}
