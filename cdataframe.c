#include <stdlib.h>
#include <stdio.h>
#include "cdataframe.h"

//CDataframe creation : ne pas oublier vérif si cdftype a donnée et limiter types avec size
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
