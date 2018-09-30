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

/*
Function: main_menu()
Description: This function makes a new node using
			 a given Record.
*/
Node * makeNode(Record newItem)
{
	Node *pMem = NULL;
	pMem = (Node *)malloc(sizeof(Node));

	strcpy(pMem->Data.artist, newItem.artist);
	strcpy(pMem->Data.album, newItem.album);
	strcpy(pMem->Data.song, newItem.song);
	strcpy(pMem->Data.genre, newItem.genre);
	pMem->Data.length.minutes = newItem.length.minutes;
	pMem->Data.length.seconds = newItem.length.seconds;
	pMem->Data.plays = newItem.plays;
	pMem->Data.rating = newItem.rating;

	pMem->pNext = NULL;
	pMem->pPrev = NULL;
	return pMem;
}

/*
Function: insertAtFront()
Description: This function inserts a new Record at
			 the front of the linked list.
*/
int insertAtFront(Node **pList, Record newItem)
{
	int success = 0;
	Node *pMem = NULL;

	pMem = makeNode(newItem);
	if (pMem != NULL)
	{
		success = 1;
		pMem->pNext = *pList;
		pMem->pPrev = NULL;
		if (*pList)
		{
			(*pList)->pPrev = pMem;
		}
		*pList = pMem;
	}
	return success;
}

/*
Function: printList()
Description: This function prints the contents
			 of each node in the linked list.
*/
void printList(Node *pList)
{
	while (pList != NULL)
	{
		printf("%s,", pList->Data.artist);
		printf("%s,", pList->Data.album);
		printf("%s,", pList->Data.song);
		printf("%s,", pList->Data.genre);
		printf("%d:%d,", pList->Data.length.minutes, pList->Data.length.seconds);
		printf("%d,", pList->Data.plays);
		printf("%d", pList->Data.rating);
		putchar('\n');
		pList = pList->pNext;
	}
}

/*
Function: timeDelay()
Description: This function delays the time
			 for a set amount of seconds 
			 using the time library.
*/
void timeDelay(int seconds)
{
	clock_t delay = clock();
	seconds = seconds * 1000;
	for (; clock() < delay + seconds;);
}

/*
Function: load()
Description: This function loads the record from
			 the input file into a linked list.
*/
void load(Node **pList, FILE *infile)
{
	infile = fopen("musicPlayList.csv", "r");
	char line[200] = "";
	int i = 0, j = 0, success = 0;

	while (fgets(line, 100, infile))
	{
		Record temp = { "", "", "", "",{ 0, 0 }, 0, 0 };
		if (line[0] == '\"') // if artist has quotes around it
		{
			char tempStr[100] = "";
			while (j != 2) // while quote has not been encountered twice
			{
				tempStr[i] = line[i];
				if (line[i] == '\"')
				{
					j++;
				}
				i++;
			}
			i = 0;
			j = 0;
			strcpy(temp.artist, tempStr);
			strtok(line, ",");
			strtok(NULL, ",");
		}
		else // if artist doesn't have quotes around it
		{
			char *pArtistNoQuote = strtok(line, ",");
			strcpy(temp.artist, pArtistNoQuote);
		}

		char *pAlbum = strtok(NULL, ",");
		strcpy(temp.album, pAlbum);

		char *pSong = strtok(NULL, ",");
		strcpy(temp.song, pSong);

		char *pGenre = strtok(NULL, ",");
		strcpy(temp.genre, pGenre);

		char *pMinutes = strtok(NULL, ":");
		temp.length.minutes = atoi(pMinutes);

		char *pSeconds = strtok(NULL, ",");
		temp.length.seconds = atoi(pSeconds);

		char *pPlays = strtok(NULL, ",");
		temp.plays = atoi(pPlays);

		char *pRating = strtok(NULL, "\n");
		temp.rating = atoi(pRating);

		success = insertAtFront(pList, temp);
	}
	fclose(infile);
}

/*
Function: display()
Description: This displays either all records from the
			 linked list, or just the records corresponding
			 to a certain artist.
*/
void display(Node *pList)
{
	int choice = 0;
	char artist[100] = "";
	printf("1. Print all records.\n2. Print all records that match an artist\nEnter a number (1-2): ");
	scanf("%d", &choice);
	getchar();
	if (choice == 1) // print full list
	{
		putchar('\n');
		printList(pList);
		putchar('\n');
	}
	else // print list based on artist
	{
		printf("*For artists with a first and last name, enter: \"Last, First\"\n");
		printf("Enter an artist to display: ");
		fgets(artist, 100, stdin);
		strtok(artist, "\n");
		putchar('\n');
		while (pList != NULL)
		{
			if (strcmp(pList->Data.artist, artist) == 0)
			{
				printf("%s,", pList->Data.artist);
				printf("%s,", pList->Data.album);
				printf("%s,", pList->Data.song);
				printf("%s,", pList->Data.genre);
				printf("%d:%d,", pList->Data.length.minutes, pList->Data.length.seconds);
				printf("%d,", pList->Data.plays);
				printf("%d", pList->Data.rating);
				putchar('\n');
			}
			pList = pList->pNext;
		}
		putchar('\n');
	}
}

/*
Function: store()
Description: This stores the current contents of the linked
			 list into the output file.
*/
void store(Node *pList, FILE *infile)
{
	infile = fopen("musicPlayList.csv", "w");
	while (pList != NULL)
	{
		fprintf(infile, "%s,", pList->Data.artist);
		fprintf(infile, "%s,", pList->Data.album);
		fprintf(infile, "%s,", pList->Data.song);
		fprintf(infile, "%s,", pList->Data.genre);
		fprintf(infile, "%d:%d,", pList->Data.length.minutes, pList->Data.length.seconds);
		fprintf(infile, "%d,", pList->Data.plays);
		fprintf(infile, "%d\n", pList->Data.rating);
		pList = pList->pNext;
	}
	fclose(infile);
}

void edit(Node *pList)
{
	char artist[100] = "", answer = '\0';
	int attIndex;
	getchar();
	printf("*For artists with a first and last name, enter: \"Last, First\"\n");
	printf("Enter an artist: ");
	fgets(artist, 100, stdin);
	strtok(artist, "\n");
	putchar('\n');
	while (pList != NULL)
	{
		if (strcmp(pList->Data.artist, artist) == 0) // if entered artists matches with artist in list
		{
			printf("%s,", pList->Data.artist);
			printf("%s,", pList->Data.album);
			printf("%s,", pList->Data.song);
			printf("%s,", pList->Data.genre);
			printf("%d:%d,", pList->Data.length.minutes, pList->Data.length.seconds);
			printf("%d,", pList->Data.plays);
			printf("%d", pList->Data.rating);
			putchar('\n');

			printf("Edit this record? (y/n): ");
			scanf(" %c", &answer);

			if (answer == 'y')
			{
				break;
			}
		}
		pList = pList->pNext;
	}
	if (answer == 'n')
	{
		printf("\nNo more records of this artist exist, editing the current record.\n\n");
	}
	printf("\n[0]artist [1]album [2]song [3]genre \n[4]length [5]plays [6]rating\n");
	printf("Enter the index of the attribute you would like to change: ");
	scanf("%d", &attIndex);
	putchar('\n');
	if (attIndex == 0) // depending on what the index chose is, edit that part of the list
	{
		char artist[100] = "";
		printf("Enter a new artist name: ");
		scanf("%s", &artist);
		strcpy(pList->Data.artist, artist);
	}
	else if (attIndex == 1)
	{
		char album[100] = "";
		printf("Enter a new album name: ");
		scanf("%s", &album);
		strcpy(pList->Data.album, album);
	}
	else if (attIndex == 2)
	{
		char song[100] = "";
		printf("Enter a new song name: ");
		scanf("%s", &song);
		strcpy(pList->Data.song, song);
	}
	else if (attIndex == 3)
	{
		char genre[100] = "";
		printf("Enter a new genre: ");
		scanf("%s", &genre);
		strcpy(pList->Data.genre, genre);
	}
	else if (attIndex == 4)
	{
		int minute = 0, second = 0;
		printf("Enter new minutes: ");
		scanf("%d", &minute);
		printf("Enter new seconds: ");
		scanf("%d", &second);
		pList->Data.length.minutes = minute;
		pList->Data.length.seconds = second;
	}
	else if (attIndex == 5)
	{
		int plays = 0;
		printf("Enter new play count: ");
		scanf("%d", &plays);
		pList->Data.plays = plays;
	}
	else
	{
		int rating = 0;
		printf("Enter new rating: ");
		scanf("%d", &rating);
		pList->Data.rating = rating;
	}
}

/*
Function: rate()
Description: This allows the user to rate a song
			 in the linked list, the record is updated
			 with the new rating.
*/
void rate(Node *pList)
{
	char song[100] = "";
	int rating = 0;

	getchar();
	printf("Enter the song you would like to rate: ");
	fgets(song, 100, stdin);
	strtok(song, "\n");

	while ((rating < 1) || (rating > 5)) // while rating is between 1 and 5
	{
		printf("Enter the rating you would like to give it (1-5): ");
		scanf("%d", &rating);
	}
	while (pList != NULL)
	{
		if (strcmp(pList->Data.song, song) == 0)
		{
			pList->Data.rating = rating; // replace rating with new rating
		}
		pList = pList->pNext;
	}
}

/*
Function: play()
Description: This function plays the Records in the linked
			 list starting at a specific artist.
*/
void play(Node *pList)
{
	char song[100] = "";
	int i = 0, j = 0;
	getchar();
	printf("Enter the song you would like to begin playing at: ");
	fgets(song, 100, stdin);
	strtok(song, "\n");
	system("cls");
	while (pList != NULL)
	{
		if (strcmp(pList->Data.song, song) == 0)
		{
			i++;
		}
		if (i > 0) // print the everything after the song that is chosen to start playing at
		{
			printf("%s,", pList->Data.artist);
			printf("%s,", pList->Data.album);
			printf("%s,", pList->Data.song);
			printf("%s,", pList->Data.genre);
			printf("%d:%d,", pList->Data.length.minutes, pList->Data.length.seconds);
			printf("%d,", pList->Data.plays);
			printf("%d\n", pList->Data.rating);
			timeDelay(2);
			system("cls");
		}
		pList = pList->pNext;
	}
}

/*
Function: main_menu()
Description: This function uses all the other functions
			 to play and diplay the main menu.
*/
void main_menu(Node *pList, FILE *infile)
{
	int choice = 0, j = 0, size = 0;

	char song[100] = "";
	Record *Data = NULL;
	Data = (Record *)malloc(sizeof(Record));
	int arr[100] = { 0 };

	while (choice != 11)
	{
		printf("(1) load\n(2) store\n(3) display\n(4) insert\n(5) delete\n\
(6) edit\n(7) sort\n(8) rate\n(9) play\n(10) shuffle\n(11) exit\n\nEnter a choice (1-11): ");
		scanf("%d", &choice);
		system("cls");
		switch (choice) {
		case 1:
			if (j == 0)
			{
				load(&pList, infile);
				printf("Loaded sucessfully\n");
				++j;
			}
			else
			{
				printf("The playlist has already been loaded.\n");
			}
			break;
		case 2:
			store(pList, infile);
			printf("Stored sucessfully\n");
			break;
		case 3:
			display(pList);
			break;
		case 4:
			getchar();
			getData(Data);
			insert(&pList, Data);
			break;
		case 5:
			getchar();
			getSong(song);
			delete(&pList, song);
			break;
		case 6:
			edit(pList);
			break;
		case 7:
			sort(&pList);
			break;
		case 8:
			rate(pList);
			break;
		case 9:
			play(pList);
			break;
		case 10:
			size = listSize(pList);
			randPlayOrder(size, arr);
			shuffle(pList, arr, size);
			break;
		case 11:
			store(pList, infile);
			break;
		default:
			system("cls");
		}
		if (choice != 11)
		{
			system("pause");
			system("cls");
		}
	}

}

/*
Function: main_menu()
Description: This function allows a new piece of data
			 to be inserted at the front of the list.
*/
int insert(Node **pList, Record *newData)
{
	int success = 0;
	
	Record inData = { "", "", "", "",{ 0, 0 }, 0, 0 };

	strcpy(inData.artist, newData->artist);
	strcpy(inData.album, newData->album);
	strcpy(inData.song, newData->song);
	strcpy(inData.genre, newData->genre);
	inData.length.minutes = newData->length.minutes;
	inData.length.seconds = newData->length.seconds;
	inData.plays = newData->plays;
	inData.rating = newData->rating;

	if ((5 >= newData->rating >= 1) && (newData->plays > 0)) // Insert if the new data accords to the rules
	{
		insertAtFront(pList, inData);
		success = 1;
	}
	else
	{
		success = 0;
	}
	return success;
}

/*
Function: getData()
Description: This requests data to be put in a new record
			 and returns a pointer to that record.
*/
void getData(Record *data)
{
	char artist[100] = "", album[100] = "", song[100] = "", genre[100] = "";
	int minutes = 0, seconds = 0, plays = 0, rating = 0;

	printf("Enter an artist: "); // Get data
	fgets(artist, 100, stdin);
	strtok(artist, "\n");

	printf("Enter an album name: ");
	fgets(album, 100, stdin);
	strtok(album, "\n");

	printf("Enter a song name: ");
	fgets(song, 100, stdin);
	strtok(song, "\n");

	printf("Enter a genre: ");
	fgets(genre, 100, stdin);
	strtok(genre, "\n");

	printf("Enter the minutes of the song: ");
	scanf("%d", &minutes);

	printf("Enter the seconds of the song: ");
	scanf("%d", &seconds);

	printf("Enter the number of plays: ");
	scanf("%d", &plays);

	printf("Enter a rating (1-5): ");
	scanf("%d", &rating);

	strcpy(data->artist, artist);
	strcpy(data->album, album);
	strcpy(data->song, song);
	strcpy(data->genre, genre);
	data->length.minutes = minutes;
	data->length.seconds = seconds;
	data->plays = plays;
	data->rating = rating;
}

/*
Function: delete()
Description: This functions deletes a certain song
			 in the linked list. A large majority
			 of this was given by Andy in class.
*/
int delete(Node **pList, char *song)
{
	int success = 0;
	Node *pCur = *pList, *pPrev = NULL, *pNext = NULL;

	while ((pCur != NULL) && (strcmp(pCur->Data.song, song) != 0))
	{
		pPrev = pCur;
		pCur = pCur->pNext;
		pNext = pCur->pNext;
	}
	if (pCur != NULL)
	{
		if(pPrev != NULL) // not first node
		{
			pPrev->pNext = pCur->pNext;
			pNext->pPrev = pPrev;
			success = 1;
		}
		else
		{
			*pList = pCur->pNext;
			success = 1;
		}
		free(pCur);
	}
	return success;
}

/*
Function: getSong()
Description: This function gets a song
			 specified by the user.
*/
char *getSong(char *song)
{
	printf("Enter a song you want to delete: "); // Get data
	fgets(song, 100, stdin);
	strtok(song, "\n");

	return song;
}

/*
Function: bubbleSortRating()
Description: This function bubble sorts the list
			 based on rating.
*/
void bubbleSortRating(Node **pList)
{
	int i = 0, size = 0, passes = 0;
	Node *pCur = *pList, *pNext = pCur->pNext;

	while (pCur != NULL)
	{
		pCur = pCur->pNext;
		size++;
	}

	pCur = *pList;
	passes = 0;

	while (passes < size)
	{
		while (pCur->pNext != NULL)
		{
			if ((pCur->Data.rating > pNext->Data.rating) && (pNext != NULL))
			{
				Node *pTemp = (Node *)malloc(sizeof(Node));
				pTemp->Data.length.minutes = pNext->Data.length.minutes;
				pTemp->Data.length.seconds = pNext->Data.length.seconds;
				pTemp->Data.rating = pNext->Data.rating;
				pTemp->Data.plays = pNext->Data.plays;
				strcpy(pTemp->Data.artist, pNext->Data.artist);
				strcpy(pTemp->Data.album, pNext->Data.album);
				strcpy(pTemp->Data.genre, pNext->Data.genre);
				strcpy(pTemp->Data.song, pNext->Data.song);

				pNext->Data.length.minutes = pCur->Data.length.minutes;
				pNext->Data.length.seconds = pCur->Data.length.seconds;
				pNext->Data.rating = pCur->Data.rating;
				pNext->Data.plays = pCur->Data.plays;
				strcpy(pNext->Data.artist, pCur->Data.artist);
				strcpy(pNext->Data.album, pCur->Data.album);
				strcpy(pNext->Data.genre, pCur->Data.genre);
				strcpy(pNext->Data.song, pCur->Data.song);

				pCur->Data.length.minutes = pTemp->Data.length.minutes;
				pCur->Data.length.seconds = pTemp->Data.length.seconds;
				pCur->Data.rating = pTemp->Data.rating;
				pCur->Data.plays = pTemp->Data.plays;
				strcpy(pCur->Data.artist, pTemp->Data.artist);
				strcpy(pCur->Data.album, pTemp->Data.album);
				strcpy(pCur->Data.genre, pTemp->Data.genre);
				strcpy(pCur->Data.song, pTemp->Data.song);
			}
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}
		pCur = *pList;
		pNext = pCur->pNext;
		passes++;
	}
}

/*
Function: bubbleSortPlays()
Description: This function bubble sorts the list
			 based on plays.
*/
void bubbleSortPlays(Node **pList)
{
	int i = 0, size = 0, passes = 0;
	Node *pCur = *pList, *pNext = pCur->pNext;

	while (pCur != NULL)
	{
		pCur = pCur->pNext;
		size++;
	}

	pCur = *pList;
	passes = 0;

	while (passes < size)
	{
		while (pCur->pNext != NULL)
		{
			if ((pCur->Data.plays > pNext->Data.plays) && (pNext != NULL))
			{
				Node *pTemp = (Node *)malloc(sizeof(Node));
				pTemp->Data.length.minutes = pNext->Data.length.minutes;
				pTemp->Data.length.seconds = pNext->Data.length.seconds;
				pTemp->Data.rating = pNext->Data.rating;
				pTemp->Data.plays = pNext->Data.plays;
				strcpy(pTemp->Data.artist, pNext->Data.artist);
				strcpy(pTemp->Data.album, pNext->Data.album);
				strcpy(pTemp->Data.genre, pNext->Data.genre);
				strcpy(pTemp->Data.song, pNext->Data.song);

				pNext->Data.length.minutes = pCur->Data.length.minutes;
				pNext->Data.length.seconds = pCur->Data.length.seconds;
				pNext->Data.rating = pCur->Data.rating;
				pNext->Data.plays = pCur->Data.plays;
				strcpy(pNext->Data.artist, pCur->Data.artist);
				strcpy(pNext->Data.album, pCur->Data.album);
				strcpy(pNext->Data.genre, pCur->Data.genre);
				strcpy(pNext->Data.song, pCur->Data.song);

				pCur->Data.length.minutes = pTemp->Data.length.minutes;
				pCur->Data.length.seconds = pTemp->Data.length.seconds;
				pCur->Data.rating = pTemp->Data.rating;
				pCur->Data.plays = pTemp->Data.plays;
				strcpy(pCur->Data.artist, pTemp->Data.artist);
				strcpy(pCur->Data.album, pTemp->Data.album);
				strcpy(pCur->Data.genre, pTemp->Data.genre);
				strcpy(pCur->Data.song, pTemp->Data.song);
			}
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}
		pCur = *pList;
		pNext = pCur->pNext;
		passes++;
	}
}

/*
Function: bubbleSortAlbum()
Description: This function bubble sorts the list
			 based on album.
*/
void bubbleSortAlbum(Node **pList)
{
	int i = 0, size = 0, passes = 0;
	Node *pCur = *pList, *pNext = pCur->pNext;

	while (pCur != NULL)
	{
		pCur = pCur->pNext;
		size++;
	}

	pCur = *pList;
	passes = 0;

	while (passes < size)
	{
		while (pCur->pNext != NULL)
		{
			if ((strcmp(pCur->Data.album, pNext->Data.album) > 0) && (pNext != NULL))
			{
				Node *pTemp = (Node *)malloc(sizeof(Node));
				pTemp->Data.length.minutes = pNext->Data.length.minutes;
				pTemp->Data.length.seconds = pNext->Data.length.seconds;
				pTemp->Data.rating = pNext->Data.rating;
				pTemp->Data.plays = pNext->Data.plays;
				strcpy(pTemp->Data.artist, pNext->Data.artist);
				strcpy(pTemp->Data.album, pNext->Data.album);
				strcpy(pTemp->Data.genre, pNext->Data.genre);
				strcpy(pTemp->Data.song, pNext->Data.song);

				pNext->Data.length.minutes = pCur->Data.length.minutes;
				pNext->Data.length.seconds = pCur->Data.length.seconds;
				pNext->Data.rating = pCur->Data.rating;
				pNext->Data.plays = pCur->Data.plays;
				strcpy(pNext->Data.artist, pCur->Data.artist);
				strcpy(pNext->Data.album, pCur->Data.album);
				strcpy(pNext->Data.genre, pCur->Data.genre);
				strcpy(pNext->Data.song, pCur->Data.song);

				pCur->Data.length.minutes = pTemp->Data.length.minutes;
				pCur->Data.length.seconds = pTemp->Data.length.seconds;
				pCur->Data.rating = pTemp->Data.rating;
				pCur->Data.plays = pTemp->Data.plays;
				strcpy(pCur->Data.artist, pTemp->Data.artist);
				strcpy(pCur->Data.album, pTemp->Data.album);
				strcpy(pCur->Data.genre, pTemp->Data.genre);
				strcpy(pCur->Data.song, pTemp->Data.song);
			}
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}
		pCur = *pList;
		pNext = pCur->pNext;
		passes++;
	}
}

/*
Function: bubbleSortArtist()
Description: This function bubble sorts the list
			 based on artist.
*/
void bubbleSortArtist(Node **pList)
{
	int i = 0, size = 0, passes = 0, j = 0, n = 0, t = 0;
	Node *pCur = *pList, *pNext = pCur->pNext;
	char curArtist[100] = "", first[100] = "", last[100] = "", nextArtist[100] = "";
	char temp1[100] = "", temp2[100] = "";

	while (pCur != NULL)
	{
		pCur = pCur->pNext;
		size++;
	}

	pCur = *pList;
	passes = 0;

	while (passes < size)
	{
		while (pCur->pNext != NULL)
		{
			char artist[100] = "";
			char nartist[100] = "";
			strcpy(artist, pCur->Data.artist);
			strcpy(nartist, pNext->Data.artist);
			strcpy(temp1, cleanArtist(artist)); // the clean artist function allows the artist names to be compared properly
			strcpy(temp2, cleanArtist(nartist));
			if ((strcmp(temp1, temp2) > 0) && (pNext != NULL))
			{
				Node *pTemp = (Node *)malloc(sizeof(Node));
				pTemp->Data.length.minutes = pNext->Data.length.minutes;
				pTemp->Data.length.seconds = pNext->Data.length.seconds;
				pTemp->Data.rating = pNext->Data.rating;
				pTemp->Data.plays = pNext->Data.plays;
				strcpy(pTemp->Data.artist, pNext->Data.artist);
				strcpy(pTemp->Data.album, pNext->Data.album);
				strcpy(pTemp->Data.genre, pNext->Data.genre);
				strcpy(pTemp->Data.song, pNext->Data.song);

				pNext->Data.length.minutes = pCur->Data.length.minutes;
				pNext->Data.length.seconds = pCur->Data.length.seconds;
				pNext->Data.rating = pCur->Data.rating;
				pNext->Data.plays = pCur->Data.plays;
				strcpy(pNext->Data.artist, pCur->Data.artist);
				strcpy(pNext->Data.album, pCur->Data.album);
				strcpy(pNext->Data.genre, pCur->Data.genre);
				strcpy(pNext->Data.song, pCur->Data.song);

				pCur->Data.length.minutes = pTemp->Data.length.minutes;
				pCur->Data.length.seconds = pTemp->Data.length.seconds;
				pCur->Data.rating = pTemp->Data.rating;
				pCur->Data.plays = pTemp->Data.plays;
				strcpy(pCur->Data.artist, pTemp->Data.artist);
				strcpy(pCur->Data.album, pTemp->Data.album);
				strcpy(pCur->Data.genre, pTemp->Data.genre);
				strcpy(pCur->Data.song, pTemp->Data.song);
			}
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}
		pCur = *pList;
		pNext = pCur->pNext;
		passes++;
	}
}

/*
Function: sort()
Description: This function uses the bubble sort functions to
			 allow the user to choose how to sort the list.
*/
void sort(Node **pList)
{
	int choice = 0;
	printf("1. Sort based on artist (A-Z) (based on first then last name)\n"); // Get input
	printf("2. Sort based on album title (A-Z)\n");
	printf("3. Sort based on rating (1-5)\n");
	printf("4. Sort based on times played (largest-smallest)\n");
	printf("Enter an option (1-4): ");
	scanf("%d", &choice);
	switch (choice){ // Sort using the different bubble sort functions written
	case 1:
		bubbleSortArtist(pList);
		break;
	case 2:
		bubbleSortAlbum(pList);
		break;
	case 3:
		bubbleSortRating(pList);
		break;
	case 4:
		bubbleSortPlays(pList);
		break;
	}
}

/*
Function: cleanArtist()
Description: This function cleans up the artist name.
*/
char *cleanArtist(char *artist)
{
	int j = 0;
	char newArtist[100] = "";
	char newFirst[100] = "";
	char newLast[100] = "";

	strcpy(newArtist, artist);

	if (newArtist[0] == '\"') // if artist is "Last, First", the string is changed to: First Last
	{
		char *last = strtok(newArtist, ",");
		*last++;
		char *first = strtok(NULL, "\"");
		*first++;
		strcpy(newLast, last);
		strcpy(newFirst, first);
		strcat(newFirst, newLast);
		return newFirst;
	}
	else
	{
		return newArtist;
	}
}

/*
Function: listSize()
Description: This function returns the list size.
*/
int listSize(Node *pList)
{
	Node *pCur = pList;
	int size = 0;

	while (pCur != NULL) // loop to find list size
	{
		pCur = pCur->pNext;
		size++;
	}
	return size;
}

/*
Function: randPlayOrder()
Description: This function uses the linked list size to create
			 a random play order, returning an array.
*/
int *randPlayOrder(int size, int arr[])
{
	int i = 0, s = 0, t = 0, j = 0;

	for (i = 0; i < size; i++) // use the rand() function to put random values in an arr for a random play order
	{
		s = 1;
		while (s != 0)
		{
			j = rand() % size + 1;
			s = 0;
			for (t = 0; t < size; t++)
			{
				if (j == arr[t])
				{
					s++;
				}
			}
		}
		arr[i] = j;
	}
	return arr;

}

/*
Function: shuffle()
Description: This function plays the linked lists records
			 in a shuffled order based on the shuffled array
			 and the linked list size.
*/
int shuffle(Node *pList, int arr[], int size)
{
	Node *pCur = pList;
	int i = 0, randLocation = 0, curLocation = 0, success = 0;

	for (i = 0; i < size; i++) // for each index of arr, get to the random location in the list and print it
	{
		randLocation = arr[i] - 1; // now have (0-size)

		if (randLocation > curLocation) // traverse to that part of the list
		{
			while (curLocation != randLocation)
			{
				pCur = pCur->pNext;
				curLocation++;
				success = 1;
			}
		}
		else
		{
			while (curLocation != randLocation) // traverse to that part of the list
			{
				pCur = pCur->pPrev;
				curLocation--;
				success = 1;
			}
		}

		printf("%s,", pCur->Data.artist);
		printf("%s,", pCur->Data.album);
		printf("%s,", pCur->Data.song);
		printf("%s,", pCur->Data.genre);
		printf("%d:%d,", pCur->Data.length.minutes, pCur->Data.length.seconds);
		printf("%d,", pCur->Data.plays);
		printf("%d\n", pCur->Data.rating);
		timeDelay(2);
		system("cls");

		curLocation = randLocation;
	}
	return success;
}