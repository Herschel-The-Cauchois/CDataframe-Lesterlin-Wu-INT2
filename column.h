#ifndef CDATAFRAMEPROJECT_COLUMN_H
#define CDATAFRAMEPROJECT_COLUMN_H

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
