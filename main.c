#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"
#include "cdataframe.h"

int main() {
    ENUM_TYPE cdftype[] = {UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE};
    CDATAFRAME* dataframe = create_cdataframe(cdftype, 7); //Creates a simple dataframe with each type in one column.
    printf("\nWelcome to CDataframe DEMO ! A Project by WU Julien and LESTERLIN Raphaël at EFREI.");
    fill_cdataframe(dataframe);
    unsigned int choice = 0;
    while (choice <= 14) {
        printf("\nAfter creating your dataframe, you have now reached the main menu. What do you wish to do with your dataframe ?");
        printf("\n[1] Display the entire Dataframe;");
        printf("\n[2] Display columns until a limit;");
        printf("\n[3] Display all columns but rows until a limit;");
        printf("\n[4] Add a row of values;");
        printf("\n[5] Delete a specific row of values;");
        printf("\n[6] Add a new column;");
        printf("\n[7] Delete a specific column;");
        printf("\n[8] Rename a column;");
        printf("\n[9] Look for a value;");
        printf("\n[10] Access and maybe replace a value;");
        printf("\n[11] Display column names;");
        printf("\n[12] Display number of rows and columns;");
        printf("\n[13] Take a value and proceeds to display the cells equal, inferior or superior to said value;");
        printf("\n[14] Quit and free the dataframe;");
        while (choice > 14 || choice < 1) {
            printf("\nEnter a value : ");
            scanf("%u", &choice);
        }
        switch (choice) {

            case 1:
                display_cdataframe(dataframe);
                choice = 0;
                break;
            case 2:
                printf("\t");
                int limit = 0;
                while (limit < 1) {
                    printf("\nPlease enter a limit : ");
                    scanf("%d", &limit);
                }
                display_cdataframe_col_limited(dataframe, limit);
                choice = 0;
                break;
            case 3:
                printf("\t");
                unsigned long long int limit2 = 0;
                while (limit2 < 1) {
                    printf("\nPlease enter a limit : ");
                    scanf("%llu", &limit2);
                }
                display_cdataframe_row_limited(dataframe, limit2);
                choice = 0;
                break;
            case 4:
                printf("\t");
                int choice2 = -1;
                while (choice2 < 0 || choice2 > 1) {
                    printf("\nDo you prefer hard filling (1) or user filling (0) ? : ");
                    scanf("%d", &choice2);
                }
                add_row(dataframe, choice2);
                choice = 0;
                break;
            case 5:
                printf("\t");
                unsigned long long int index = 0;
                while (index < 1) {
                    printf("\nPlease enter an index : ");
                    scanf("%llu", &index);
                }
                delete_row(dataframe, index);
                choice = 0;
                break;
            case 6:
                add_col(dataframe);
                int choice3 = -1;
                while (choice3 < 0 || choice3 > 1) {
                    printf("\nDo you prefer hard filling (1) or user filling (0) ? : ");
                    scanf("%d", &choice3);
                }
                int* randominator = (int*) malloc(sizeof(int)); //Uses an empty variable to generate random input for hard filling.
                srand(time(NULL));
                *randominator = rand();
                COL_TYPE new_data; //For user input filling, creates a variable that can hold all the datatypes the dataframe can handle.
                switch (((COLUMN*) dataframe->tail->data)->column_type) {

                    case NULLVAL: //If the column doesn't have a type, does not bother to try filling it.
                        return 1;
                    case UINT:
                        if (choice3) { //If the hard boolean value is true, proceeds to the allocation of a random number.
                            new_data.uint_value = (unsigned int) *randominator;
                        } else { //Else, asks the user to enter a value.
                            printf("\nEnter an unsigned integer : ");
                            scanf("%u", &(new_data.uint_value));
                        }
                        insert_value(((COLUMN*) dataframe->tail->data), &new_data); //Inserts it with the column function inside.
                        break; //Repeat for all other cases.
                    case INT:
                        if (choice3) {
                            new_data.int_value = (int) *randominator;
                        } else {
                            printf("\nEnter an integer : ");
                            scanf("%d", &(new_data.int_value));
                        }
                        insert_value(((COLUMN*) dataframe->tail->data), &new_data);
                        break;
                    case CHAR:
                        if (choice3) {
                            new_data.char_value = (char) *randominator;
                        } else {
                            printf("\nEnter a character : ");
                            scanf("%c", &(new_data.char_value));
                            scanf("%c", &(new_data.char_value));
                        }
                        insert_value(((COLUMN*) dataframe->tail->data), &new_data);
                        break;
                    case FLOAT:
                        if (choice3) {
                            new_data.float_value = (float) *randominator;
                        } else {
                            printf("\nEnter a float : ");
                            scanf("%f", &(new_data.float_value));
                        }
                        insert_value(((COLUMN*) dataframe->tail->data), &new_data);
                        break;
                    case DOUBLE:
                        if (choice3) {
                            new_data.double_value = (double) *randominator;
                        } else {
                            printf("\nEnter a double float : ");
                            scanf("%lf", &(new_data.double_value));
                        }
                        insert_value(((COLUMN*) dataframe->tail->data), &new_data);
                        break;
                    case STRING:
                        if (choice3) {
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
                            printf("\nString alloc test : %s", temp2);
                            snprintf(new_data.string_value, size+1, "%s", temp2);
                            printf("\nThere should be smth here : %s", new_data.string_value);
                            //Since this member is a pointer, the string member is passed directly.
                        }
                        insert_value(((COLUMN*) dataframe->tail->data), new_data.string_value);
                        break;
                    case STRUCTURE:
                        if (choice3) {
                            ((STUDENT*) new_data.struct_value)->id = (int) *randominator;
                            ((STUDENT*) new_data.struct_value)->average = (float) abs(*randominator);
                        } else {
                            printf("\nEnter Student ID (integer) : ");
                            scanf("%d", &((STUDENT*) new_data.struct_value)->id);
                            printf("\nEnter Student average grade : ");
                            scanf("%f", &((STUDENT*) new_data.struct_value)->average);
                        }
                        insert_value(((COLUMN*) dataframe->tail->data), new_data.struct_value);
                        break;
                }
                choice = 0;
                break;
            case 11:
                display_col_names(dataframe);
                choice = 0;
                break;
            case 12:
                rows_cols(dataframe);
                choice = 0;
                break;
            case 13:
                printf("\t");
                double value = 0;
                printf("\nPlease enter a value : ");
                scanf("%lf", &value);
                printf("\nCELLS EQUAL TO VALUE ---");
                cells_equal_x(dataframe, value);
                printf("\nCELLS INFERIOR TO VALUE ---");
                cells_inferior_x(dataframe, value);
                printf("\nCELLS SUPERIOR TO VALUE ---");
                cells_superior_x(dataframe, value);
                choice = 0;
                break;
            case 14:
                choice = 15;
                break;
            default:
                choice = 0;
                break;
        }
    }
    printf("\nDeleting entire Cdataframe\n------");
    delete_cdataframe(&dataframe);
    return 0;
}
