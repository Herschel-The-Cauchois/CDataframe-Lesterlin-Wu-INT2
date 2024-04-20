# README CDataframe Project
____

## LESTERLIN Raphaël and WU Julien

<u>[Repository](https://github.com/Herschel-The-Cauchois/CDataframe-Lesterlin-Wu-INT2)</u>

This project aims to create in C a table managing several types of data in different columns, which could be understood as some kind of low-level offline SQL Database.

We implement this as a set of nested Simply Linked Lists (SLL), a double linked list for managing columns of the Dataframe (list.h and list.c files) and a double linked list as the data of each column to manage more efficiently the rows (column.h and column.c).

The main.c file is planned to hold the future menu for dataframe manipulations and cdataframe.c/cdataframe.h will host the functions related to such common operations.

All the other files are a product of CLion IDE project management programs. 