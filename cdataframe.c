#include <stdlib.h>
#include <stdio.h>
#include "cdataframe.h"

//CDataframe creation function
CDATAFRAME* create_cdataframe(ENUM_TYPE *cdftype, int size) {
    CDATAFRAME* dataframe = (CDATAFRAME*) malloc(sizeof(lnode)); //Initializes the dataframe.
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
    lnode* temp = start;
    //after that, for all remaining types in the cdftype array:
    for (int i = 1; i < size; i++) {
        lnode* new = (lnode*) malloc(sizeof(lnode));
        temp->next = new; //Initialises a new lnode to put to the succession of the previous, starting from
        //the head node.
        char* coltitle = (char*) malloc(20*sizeof(char));
        snprintf(coltitle, 20, "Sans nom %d", i); //Formats a default title string for each column.
        COLUMN* new_col = create_column(cdftype[i], coltitle);
        new->data = new_col; //Initializes new column and puts it in the lnode's data.
        temp = temp->next; //Goes to next lnode.
    }
    dataframe->tail = temp; //Sets tail of the dataframe as the last lnode put in temp.
    return dataframe;
}

void delete_column(CDATAFRAME *cdf, char *col_name) {
    lnode* temp = cdf->head; //Creates temporary pointer that points to the start node.
    COLUMN* col;
    while (temp->next != NULL || col->title != col_name) {
        if (temp->data != NULL) {
            col = (COLUMN *) temp->data;  //The col pointer will then each time point at the column data of the node.
            printf("\n%u", col->column_type);  //Prints the column type if it finds it.
        }
        if (temp->next != NULL && temp != cdf->tail) {
            //Only if we are not at the tail node and if the next node isn't null will it go to the next one.
            temp = temp->next;
        } else {
            //The break is necessary because it was observed when arriving to the last node that it would go
            //To a ghost node that has sufficient memory allocated to pass the temp != NULL test but not enough to be
            //considered a real node. To avoid this, when it is detected that we are at the tail node it proceeds to
            //directly breaks the while.
            break;
        }
    }
    if (col->title != col_name) {
        //If the column wasn't found, ends the function?
        return;
    }
    printf("\nColumn retrieved.");
    int flag = 0;
    while (flag == 0) {
        //Until the free_value functions returns a 1 that indicates that the second element of the SLL is freed, loops.
        flag = free_value(col, 1);
    }
    free_value(col, 0); //Frees the head of the column.
    free(col);  //Frees the data attribute of the node itself.
    if (temp->prev != NULL) {
        //If the concerned node isn't at the head of the Cdataframe, sets its predecessor's successor to the
        //Successor of the node.
        temp->prev->next = temp->next;
    } else {
        //If it is, just puts at the head of the cdataframe the successor of the current node.
        cdf->head = temp->next;
    }
    printf("\nColumn deleted !");
    lst_delete_lnode(cdf, temp); //Attempt at freeing the now useless node of the deleted column.
    printf("\nColumn deleted !");
    //With Free, it yields 0xC0000FD error, and with this function 0xC0000374.
}

int get_cdataframe_cols_size(CDATAFRAME *cdf) {}

void cells_equal_x(CDATAFRAME *cdf, float x) {
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
                    if ((float) col_explorer->data.int_value == x) {
                        printf("\n%llu | %d", i, col_explorer->data.int_value);
                    } else if (col_explorer->data.float_value == x) {
                        printf("\n%llu | %.5f", i, col_explorer->data.float_value);
                    } else if ((float) col_explorer->data.double_value == x) {
                        printf("\n%llu | %.5lf", i, col_explorer->data.double_value);
                    } else if ((float) col_explorer->data.uint_value == x) {
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

void cells_superior_x(CDATAFRAME *cdf, float x) {
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

void cells_inferior_x(CDATAFRAME *cdf, float x) {
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
