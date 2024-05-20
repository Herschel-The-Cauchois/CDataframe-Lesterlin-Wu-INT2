# README CDataframe Project
____

## LESTERLIN Raphaël and WU Julien

<u>[Repository](https://github.com/Herschel-The-Cauchois/CDataframe-Lesterlin-Wu-INT2)</u>

This project aims to create in C a table managing several types of data in different columns, which could be understood as some kind of low-level offline SQL Database.

We implement this as a set of nested Simply Linked Lists (SLL), a double linked list for managing columns of the Dataframe (list.h and list.c files) and a double linked list as the data of each column to manage more efficiently the rows (column.h and column.c).

The main.c file holds the menu for dataframe manipulations and cdataframe.c/cdataframe.h hosts the functions related to such common operations. Other files manage the different types, structures and functions the program manipulates to provide the best user experience possible to manage the data.

All the other files are a product of CLion IDE project management programs. You may execute the program by opening the files in a CLion session in a project, or use any available C compiler to get a binary (.exe file) and double-click to run. Antivirus be not afraid : our low-level program isn't a virus :)