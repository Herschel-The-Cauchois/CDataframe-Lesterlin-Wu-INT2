#include <stdio.h>
#include <stdlib.h>
#include "column.h"

//This function creates an empty column.
COLUMN *create_column(ENUM_TYPE type, char *title) {
    COLUMN* col;
    col = (COLUMN*) malloc(sizeof(COLUMN)); //Allocates the memory necessary to such empty column.
    col->column_type = type;
    col->title = title; //Associates the given parameters to its title and type properties.
    col->data = NULL;
    col->index = NULL;
    col->size = 0;
    col->max_size = 256;
    col->index = 0; //Sets everything else to default values.
    return col;
};

//This function inserts a value inside a column.
int insert_value(COLUMN *col, void *value) {
    if (col->size + sizeof(value) > col->max_size) {
        //If the size of the column + the size of the value is above the physical sizes, allocates a supplementary
        //256 bits.
        realloc(col, col->max_size + 256);
    }
        if (col->data != NULL) {
            //This scenario happens if the data attribute has already an SLL in it, hence != NULL.
            DATARRAY* temp = col->data; //Creates a pointer to the column's first SLL node.
            while (temp->next != NULL) {
                //Moves the pointer to the successor node until it reaches the last node with NULL as successor.
                temp = temp->next;
            }
            DATARRAY* new_node; //Creates a new node for the new value.
            new_node = (DATARRAY*) malloc(sizeof(DATARRAY)); //Allocates memory to it.
            switch (col->column_type) {
                //According to the type of data the column handles, will always assign NULL to the successor of the new
                //node, then set his predecessor as the last node of the SLL and the new node as temp's successor.
                //Finally, to better handle displaying it will cast a type to the entered value pointer through an
                //intermediate pointer before assigning to the data of the new node the expected value, to the correct
                //member of the union.
                case NULLVAL:
                    printf("Error : No type cast to column.");
                    free(new_node);
                    return 1;
                case UINT:
                    new_node->prev = temp;
                    new_node->next = NULL;
                    temp->next = new_node;
                    unsigned int* value2 = (unsigned int*) value;
                    new_node->data.uint_value = *value2;
                    col->size += sizeof(unsigned int);
                    break;
                case INT:
                    new_node->prev = temp;
                    new_node->next = NULL;
                    temp->next = new_node;
                    int* value3 = (int*) value;
                    new_node->data.int_value = *value3;
                    col->size += sizeof(int);
                    break;
                case CHAR:
                    new_node->prev = temp;
                    new_node->next = NULL;
                    temp->next = new_node;
                    char* value4 = (char*) value;
                    new_node->data.char_value = *value4;
                    col->size += sizeof(char);
                    break;
                case FLOAT:
                    new_node->prev = temp;
                    new_node->next = NULL;
                    temp->next = new_node;
                    float* value5 = (float*) value;
                    new_node->data.float_value = *value5;
                    col->size += sizeof(float);
                    break;
                case DOUBLE:
                    new_node->prev = temp;
                    new_node->next = NULL;
                    temp->next = new_node;
                    double* value6 = (double*) value;
                    new_node->data.double_value = *value6;
                    col->size += sizeof(double);
                    break;
                case STRING:
                    new_node->prev = temp;
                    new_node->next = NULL;
                    temp->next = new_node;
                    char* value7 = (char*) value;
                    new_node->data.string_value = value7;
                    col->size += sizeof(value7);
                    break;
                case STRUCTURE:
                    new_node->prev = temp;
                    new_node->next = NULL;
                    temp->next = new_node;
                    new_node->data.struct_value = value;
                    col->size += sizeof(value);
                    break;
            }
            return 0;
        } else {
            DATARRAY* new_node;
            new_node = (DATARRAY*) malloc(sizeof(DATARRAY)); //Creates and allocates memory to the new node
            //Holding the value we want to insert.
            new_node->prev = NULL;
            new_node->next = NULL;
            col->data = new_node; //Creates the SLL in the column's data if not existent.
            switch (col->column_type) {
                //Same stuff happening for the already existing SLL case.
                case NULLVAL:
                    printf("\nError : No type cast to column.");
                    free(new_node);
                    return 1;
                case UINT:
                    new_node = new_node; //This is absolutely necessary else C considers the following expression
                    //as invalid.
                    unsigned int* value2 = (unsigned int*) value;
                    new_node->data.uint_value = *value2;
                    col->size += sizeof(unsigned int);
                    break;
                case INT:
                    new_node = new_node;
                    int* value3 = (int*) value;
                    new_node->data.int_value = *value3;
                    col->size += sizeof(int);
                    break;
                case CHAR:
                    new_node = new_node;
                    char* value4 = (char*) value;
                    new_node->data.char_value = *value4;
                    col->size += sizeof(char);
                    break;
                case FLOAT:
                    new_node = new_node;
                    float* value5 = (float*) value;
                    new_node->data.float_value = *value5;
                    col->size += sizeof(float);
                    break;
                case DOUBLE:
                    new_node = new_node;
                    double* value6 = (double*) value;
                    new_node->data.double_value = *value6;
                    col->size += sizeof(double);
                    break;
                case STRING:
                    new_node = new_node;
                    char* value7 = (char*) value;
                    printf("\n%s", value7);
                    new_node->data.string_value = value7;
                    col->size += sizeof(*value7);
                    break;
                case STRUCTURE:
                    new_node->data.struct_value = value;
                    col->size += sizeof(value);
                    break;
            }
            return 0;
        }
}

//This function frees a value inside a column.
int free_value(COLUMN *col, unsigned long long int index) {
    DATARRAY* linked_list = col->data;  //Create a pointer to loop through the linked list.
    unsigned long long int counter = 0;  //Creates a counter of iteration to be able to navigate through all elements.
    while (linked_list->next != NULL && counter < index) {
        //While there is a successor of the node, and we're not yet at the correct index :
        linked_list = linked_list->next; //replace linked list node by its successor
        counter++;
    }
    if (counter != index) {
        //Detects if there is no such elements of given index, if we're at the end of the list but counter isn't at
        //the expected value given by index. Returns 1 because the function failed to free any node.
        return 1;
    }
    if (linked_list->prev == NULL) {  //If we're at the head of the list :
        col->data = col->data->next;  //Makes column data attribute point to list's successor node
        free(linked_list);  //Frees concerned node.
        return 0;
    } else {  //If we're at any other given node :
        linked_list->prev->next = linked_list->next;  //Attaches back the wagons : previous node's successor becomes
        //the successor of the node we're pointing at.
        free(linked_list);  //Frees the concerned now which is now isolated from the list.
        return 0;
    }
}

//This functions places inside a buffer variable the data contained at the node at position index of the list
//converted into a string.
void display_converter(COLUMN *col, unsigned long long int index, char* buffer, int size) {
    DATARRAY* temp = col->data; //Creates a temporary pointer directing to the list's head.
    for (int i = 0; i < index; i++) {  //Loops through the list until it finds the correct node.
        temp = temp->next;
    }
    switch (col->column_type) {

        case NULLVAL:  //For each type of data, proceeds to the conversion using snprintf.
            snprintf(buffer, size, "%s", (char*) NULL);
            break;
        case UINT:
            snprintf(buffer, size, "%u", temp->data.uint_value);
            break;
        case INT:
            snprintf(buffer, size, "%d", temp->data.int_value);
            break;
        case CHAR:
            snprintf(buffer, size, "%c", temp->data.char_value);
            break;
        case FLOAT:
            snprintf(buffer, size, "%f", temp->data.float_value);
            break;
        case DOUBLE:
            snprintf(buffer, size, "%lf", temp->data.double_value);
            break;
        case STRING:
            snprintf(buffer, size, "%s", temp->data.string_value);
            break;
        case STRUCTURE:
            //C doesn't offer the possibility to reflexively access the member of its structure, hence it is not
            //possible to implement a convenient and all encompassing way of displaying structure data.
            //développer structure de test
            snprintf(buffer, size, "%s", "NOT SUPPORTED YET");
            break;
    }
}

//Function that prints the whole column given by the user.
void print_col(COLUMN* col) {
    DATARRAY* temp = col->data;
    int iterator = 0;
    char* buffer = (char*) malloc(32*sizeof(char));
    do {
        //For each node encountered, proceeds to convert it into a string, and then print it to the side of its index.
        display_converter(col, iterator, buffer, 32);
        printf("\n[%d] %s", iterator, buffer);
        temp = temp->next; //Moves to the next node and increases iterator that represents the node's index.
        iterator++;
    } while (temp != NULL);
}
