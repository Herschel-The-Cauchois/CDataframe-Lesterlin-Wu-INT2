#ifndef CDATAFRAMEPROJECT_COLUMN_H
#define CDATAFRAMEPROJECT_COLUMN_H

//Elementary structure that will be considered in the structure manipulating rows of the dataframe.
typedef struct Student {
    int id;
    float average;
}STUDENT;

enum enum_type {
    NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

union column_type {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE;

//This is done to manage separately the data inside the columns and the double linked list of the cdataframe.
typedef struct datarray {
    COL_TYPE data;
    struct datarray *prev;
    struct datarray *next;
} DATARRAY;

struct column {
    char *title;
    unsigned int size;
    unsigned int max_size;
    ENUM_TYPE column_type;
    DATARRAY *data; //The data contained in the column will be implemented as a linked list for convenience.
    unsigned long long int *index;
};

typedef struct column COLUMN;

COLUMN *create_column(ENUM_TYPE type, char *title);

int insert_value(COLUMN *col, void *value);

int free_value(COLUMN *col, unsigned long long int index);

void display_converter(COLUMN *col, unsigned long long int index, char* buffer, int size);

void print_col(COLUMN* col);


#endif //CDATAFRAMEPROJECT_COLUMN_H
