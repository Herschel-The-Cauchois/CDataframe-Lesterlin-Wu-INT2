#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "list.h"
#include "column.h"
#include "cdataframe.h"

//LESTERLIN Raphaël and WU Julien L1 INT2 - CDataframe project - This is the main program the user will interact with.

int main() {
    ENUM_TYPE cdftype[] = {UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE}; //For the demo, creates an array with all types managed.
    CDATAFRAME* dataframe = create_cdataframe(cdftype, 7); //Creates a simple dataframe with each type in one column.
    printf("\nWelcome to CDataframe DEMO ! A Project by WU Julien and LESTERLIN Raphaël at EFREI.");
    fill_cdataframe(dataframe); //Fills cdataframe following user instruction. Warning : after tests, there is technical possibility to do only 32 rows maximum. Reasons for this behavior is unknown, as putting more will yield heap corruption errors.
    unsigned int choice = 0;
    while (choice <= 14) { //Maintains the user in a selection menu until he has selected the 14th option.
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
        while (choice > 14 || choice < 1) { //Forces the user to enter a number between the allowed values.
            printf("\nEnter a value : ");
            scanf("%u", &choice);
        }
        switch (choice) {
            //Switches between each option.
            case 1:
                display_cdataframe(dataframe);
                choice = 0;
                break;
            case 2:
                printf("\t"); //Those statements are mandatory when starting by a variable declaration the specific case, else it throws errors.
                int limit = 0;
                while (limit < 1) { //Same mechanism as for the choice variable.
                    printf("\nPlease enter a limit : ");
                    scanf("%d", &limit);
                }
                display_cdataframe_col_limited(dataframe, limit); //Calls the appropriate function.
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
                            snprintf(new_data.string_value, size+1, "%s", temp2);
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
            case 7:
                printf("\t");
                char* col_buffer1 = (char*) malloc(32*sizeof(char)); //Creates a buffer that will hold user string input.
                printf("\nPlease enter the name of a column : ");
                gets(col_buffer1); //The doubling is necessary to prevent backspace filling the buffer.
                gets(col_buffer1);
                delete_column(dataframe, col_buffer1);
                choice = 0;
                break;
            case 8:
                printf("\t");
                char* col_buffer2 = (char*) malloc(32*sizeof(char)); //Same technique as above, repeated twice.
                printf("\nPlease enter the name of a column : ");
                gets(col_buffer2);
                gets(col_buffer2);
                char* col_buffer3 = (char*) malloc(32*sizeof(char));
                printf("\nPlease enter its new name : ");
                gets(col_buffer3); //Since the backspace buffer filling doesn't activate here, we only need one gets.
                rename_col(dataframe, col_buffer2, col_buffer3);
                choice = 0;
                break;
            case 9:
                printf("\t");
                int type = 1;
                while (type < 2 || type > 8) { //Secures input to obtain a type supported by the program.
                    printf("\nChoose a type for the value to search, from 2 to 8 (UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE) : ");
                    scanf("%d", &type);
                }
                switch (type) {
                    //For each case, asks the user a value to search and yields a feedback.
                    case NULLVAL: //If the column doesn't have a type, does not bother to try filling it.
                        return 1;
                    case UINT:
                        printf("\t");
                        unsigned int uint_value;
                        printf("\nEnter an unsigned integer : ");
                        scanf("%u", &uint_value);
                        if (does_value_exist(dataframe, &uint_value, UINT)) {
                            printf("\nYes!");
                        } else {
                            printf("\nNo :(");
                        }
                        break; //Repeat for all other cases.
                    case INT:
                        printf("\t");
                        int int_value;
                        printf("\nEnter an integer : ");
                        scanf("%d", &int_value);
                        if (does_value_exist(dataframe, &int_value, INT)) {
                            printf("\nYes!");
                        } else {
                            printf("\nNo :(");
                        }
                        break;
                    case CHAR:
                        printf("\t");
                        char char_value;
                        printf("\nEnter a character : ");
                        scanf("%c", &char_value);
                        scanf("%c", &char_value);
                        if (does_value_exist(dataframe, &char_value, CHAR)) {
                            printf("\nYes!");
                        } else {
                            printf("\nNo :(");
                        }
                        break;
                    case FLOAT:
                        printf("\t");
                        float float_value;
                        printf("\nEnter a float : ");
                        scanf("%f", &float_value);
                        if (does_value_exist(dataframe, &float_value, FLOAT)) {
                            printf("\nYes!");
                        } else {
                            printf("\nNo :(");
                        }
                        break;
                    case DOUBLE:
                        printf("\t");
                        double double_value;
                        printf("\nEnter a double float : ");
                        scanf("%lf", &double_value);
                        if (does_value_exist(dataframe, &double_value, DOUBLE)) {
                            printf("\nYes!");
                        } else {
                            printf("\nNo :(");
                        }
                        break;
                    case STRING:
                        printf("\t");
                        char* str_value = (char*) malloc(32*sizeof(char));
                        printf("\nEnter a string : ");
                        gets(str_value);
                        if (does_value_exist(dataframe, &str_value, STRING)) {
                            printf("\nYes!");
                        } else {
                            printf("\nNo :(");
                        }
                        break;
                    case STRUCTURE:
                        printf("\t");
                        STUDENT* struct_value = (STUDENT*) malloc(sizeof(STUDENT));
                        printf("\nEnter a student ID : ");
                        scanf("%d", &struct_value->id);
                        printf("\nEnter an average : ");
                        scanf("%f", &struct_value->average);
                        if (does_value_exist(dataframe, &struct_value, STRUCTURE)) {
                            printf("\nYes!");
                        } else {
                            printf("\nNo :(");
                        }
                        break;
                    default:
                        break;
                }
                choice = 0;
                break;
            case 10:
                printf("\t");
                unsigned long long int index1 = 0, index2 = 0;
                printf("\nPlease enter the index of a row : ");
                scanf("%llu", &index1);
                printf("\nPlease enter the index of a column : ");
                scanf("%llu", &index2);
                access_replace_value(dataframe, index1, index1);
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
            case 14: //This is the case that ends the program by putting in choice a value that makes it get out of the while loop.
                choice = 15;
                break;
            default:
                choice = 0;
                break;
        }
    }
    printf("\nDeleting entire Cdataframe\n------");
    delete_cdataframe(&dataframe); //Finally frees the cdataframe.
    printf("\nThank you for using our CDataframe Demo. We may come back with more improvements. Ciao :)");
    return 0;
}
