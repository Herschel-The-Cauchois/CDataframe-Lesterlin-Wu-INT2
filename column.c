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

int insert_value(COLUMN *col, void *value) {
    if (col->size + sizeof(value) > col->max_size) {
        realloc(col, col->max_size + 256);
    }
        if (col->data != NULL) {
            DATARRAY* temp = col->data;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            DATARRAY* new_node;
            new_node = (DATARRAY*) malloc(sizeof(DATARRAY));
            switch (col->column_type) {

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
            new_node = (DATARRAY*) malloc(sizeof(DATARRAY));
            new_node->prev = NULL;
            new_node->next = NULL;
            col->data = new_node;
            switch (col->column_type) {

                case NULLVAL:
                    printf("Error : No type cast to column.");
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



