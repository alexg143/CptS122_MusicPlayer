/*
Programmer: Alexander Glenn
Class: CptS 122; Lab Section 3
Programming Assignment: Programming Assignment 3
Date: September 21, 2018
Description: This program uses a musicPlayList.csv file
			 to use different types of functions similar to 
			 an iPod. These functions include load, store,
			 display, edit, rate, and play. The functions that
			 were added for this assignment were shuffle, sort,
			 delete, and insert. There are also test functions
			 for testing insert, delete, and shuffle.
*/

#include "header.h"

int main(void)
{
	Record *pList = NULL;
	FILE *infile = NULL;
	srand((unsigned int)time(NULL));

	
	main_menu(pList, infile);

	return 0;
}