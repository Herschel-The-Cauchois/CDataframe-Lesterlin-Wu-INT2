#ifndef CDATAFRAMEPROJECT_CDATAFRAME_H
#define CDATAFRAMEPROJECT_CDATAFRAME_H
#include "column.h"
#include "list.h"

typedef list CDATAFRAME;

CDATAFRAME* create_cdataframe(ENUM_TYPE *cdftype, int size);

void delete_column(CDATAFRAME *cdf, char *col_name);

void delete_cdataframe(CDATAFRAME **cdf);

int get_cdataframe_cols_size(CDATAFRAME *cdf);

void fill_cdataframe(CDATAFRAME *cdf);

void display_cdataframe(CDATAFRAME *cdf);

void display_cdataframe_row_limited(CDATAFRAME *cdf, int limit);

void display_cdataframe_col_limited(CDATAFRAME *cdf, int limit);

int add_row(CDATAFRAME *cdf);

int delete_row(CDATAFRAME *cdf);

int add_col(CDATAFRAME *cdf);

int rename_col(CDATAFRAME *cdf, char* column);

int does_value_exist(CDATAFRAME *cdf, void *value);

int access_replace_value(CDATAFRAME *cdf, unsigned long long int row, unsigned long long int col);

void rows_cols(CDATAFRAME *cdf); //First function of the Cdataframe statistic function

void cells_equal_x(CDATAFRAME *cdf, float x);

void cells_superior_x(CDATAFRAME *cdf, float x);

void cells_inferior_x(CDATAFRAME *cdf, float x);

#endif //CDATAFRAMEPROJECT_CDATAFRAME_H
