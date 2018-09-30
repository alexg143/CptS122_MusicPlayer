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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

typedef struct duration
{
	int minutes;
	int seconds;
} Duration;

typedef struct record
{
	char artist[100];
	char album[100];
	char song[100];
	char genre[100];
	Duration length;
	int plays;
	int rating;
} Record;

typedef struct node
{
	Record Data;
	struct node *pNext;
	struct node *pPrev;
} Node;

Node * makeNode(Record newItem);
int insertAtFront(Node **pList, Record newItem);
void printList(Node *pList);
void timeDelay(int seconds);
char *cleanArtist(char *artist);

void load(Node **pList, FILE *infile);
void display(Node *pList);
void store(Node *pList, FILE *infile);
void edit(Node *pList);
void rate(Node *pList);
void play(Node *pList);
void main_menu(Node *pList, FILE *infile);

void getData(Record *data);
int insert(Node **pList, Record *newData);

char *getSong(char *song);
int delete(Node **pList, char *song);

int listSize(Node *pList);
int *randPlayOrder(int size, int arr[]);
int shuffle(Node *pList, int arr[], int size);

void bubbleSortArtist(Node **pList);
void bubbleSortAlbum(Node **pList);
void bubbleSortRating(Node **pList);
void bubbleSortPlays(Node **pList);
void sort(Node **pList);