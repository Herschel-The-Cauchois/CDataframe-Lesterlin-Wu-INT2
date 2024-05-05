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
    //With Free, it yields 0xC000005 error, and with this function 0xC0000374.
}
