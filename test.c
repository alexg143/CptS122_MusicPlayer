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

#include "test.h"

/*
Function: testInsert()
Description: This function tests the insert() function
			 to verify it works correctly using a given
			 artist.
*/
void testInsert(void)
{
	Node *pList = NULL;
	char artist[100] = "\"Perry, Katy\"", album[100] = "Witness", song[100] = "Chained to the Rhythm", genre[100] = "Pop";
	int min = 4, sec = 36, plays = -1, rating = 6, success = 0;
	
	Record *newData = NULL;
	newData = (Record *)malloc(sizeof(Record));

	strcpy(newData->artist, artist);
	strcpy(newData->album, album);
	strcpy(newData->song, song);
	strcpy(newData->genre, genre);
	newData->length.minutes = min;
	newData->length.seconds = sec;
	newData->plays = plays;
	newData->rating = rating;

	success = insert(&pList, newData); // Testing insert function

	if (success == 1)
	{
		printf("New record successfully inserted\n");
		if (pList == NULL)
		{
			printf("Head pointer was not updated\n");
		}
		else
		{
			printf("Head pointer was updated\n");
		}
	}
	else
	{
		printf("New record not inserted successfully\n");
		printf("Either the rating was out of its bounds or the plays were negative\n");
		if (pList == NULL)
		{
			printf("Head pointer was not updated\n");
		}
		else
		{
			printf("Head pointer was updated\n");
		}
	}

}

/*
Function: testDelete()
Description: This function tests the delete() function
			 to verify it works correctly using a given
			 artist and song.
*/
void testDelete(void)
{
	Node *pList = NULL;
	Record rec = { "\"Perry, Katy\"", "Witness", "Chained to the Rhythm", "Pop",{ 4, 36 }, 3, 5 };
	int success = 0;
	char song[100] = "Chained to the Rhythm";
	insertAtFront(&pList, rec);

	success = delete(&pList, song); // Testing delete function
	
	if (success = 1)
	{
		printf("Success = 1, node deleted\n");
	}
	if (success == 1)
	{
		printf("Memory was released\n");
	}
	if (pList == NULL)
	{
		printf("Head pointer was updated to be NULL\n");
	}
}

/*
Function: testShuffle()
Description: This function tests the shuffle() function
			 to verify it works correctly using three given
			 records in a linked list.
*/
void testShuffle(void)
{
	int arr[100] = { 3, 1, 2 }; // play order that the shuffle feature will play in
	int success = 0;

	// Provide a list of 3 songs
	Node *pList = NULL;
	Record rec1 = { "\"Brooks, Garth\"", "FRESH HORSES", "The Old Stuff", "Country", {2, 57}, 11, 2 };
	Record rec2 = { "Eminem", "SHADYXV", "Vegas", "Rap", {3, 37}, 8, 3 };
	Record rec3 = { "Drake", "YOU WELCOME", "The Motto", "Rap", {4, 13}, 7, 4 };
	insertAtFront(&pList, rec1);
	insertAtFront(&pList, rec2);
	insertAtFront(&pList, rec3);
	

	success = shuffle(pList, arr, 3); // Testing shuffle function

	if (success == 1)
	{
		printf("Shuffled in the correct 3, 1, 2 order\n\n");
	}
}