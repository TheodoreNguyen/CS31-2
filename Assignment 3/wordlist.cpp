//============== NAME: Theodore Nguyen; UID: 704-156-701; Summer 2014 CS31 Vahab; Assignment 3 =======================

/* Assignment 3 source file
*
*	This file will contain the function definitions you will implement.
*	The function signitures may not be changed.  You may create your own
*	functions and include them in this file.
*
*	Topics: Multidimensional Arrays
*
*/
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cstring>
using namespace std;

/* Globally defined constants
*/
const int MAX_WORD_SIZE = 20;
const int MAX_WORD = 25;

/* Function prototypes:
*
*	declare any additional helper functions
*/

int numOfWords(const char words[][MAX_WORD_SIZE]);
void printList(char words[][MAX_WORD_SIZE]);
int findWord(char words[][MAX_WORD_SIZE], const char str[]);
void removeWord(char words[][MAX_WORD_SIZE], unsigned int i);
int removeAllInstances(char words[][MAX_WORD_SIZE], const char str[]);
int removeDuplicates(char words[][MAX_WORD_SIZE]);
void findWordSequence(char words1[][MAX_WORD_SIZE], const char words2[][MAX_WORD_SIZE], int& start, int& end);
void initialize(char words[][MAX_WORD_SIZE], const char str[], char delimiter);
int insertWord(char words[][MAX_WORD_SIZE], const char new_word[], int i);
char* findMinimum(char words[][MAX_WORD_SIZE]);


/* Main function
*
*	you may make any changes you want to main to test your functions.
*	We will be using our own to grade.
*/
int main()
{
	
	// example 
	char words1[MAX_WORD][MAX_WORD_SIZE] = { "" };
	char words2[MAX_WORD][MAX_WORD_SIZE] = { "orange", "apple", "orange", "pear", "melon", "apple", "mango" };

	// check printList and numOfWords (difficulty 1)
	int count = numOfWords(words2);
	cout << count << endl;
	printList(words2);

	// check insert (difficulty 1)
	insertWord(words2, "grape", 4);
	printList(words2);

	// check initialize  (difficulty 3)
	initialize(words1, "we are working on project 3 of course CS31 and we will finish it soon", ' ');
	printList(words1);

	// check find and remove (difficulty 1)
	int index = findWord(words1, "project");
	cout << index << endl;
	removeWord(words1, index);
	printList(words1);

	// check removeAllWord (difficulty 2)
	int count2 = removeAllInstances(words1, "we");
	cout << count2 << endl;
	printList(words1);

	// check removeDuplicates (difficulty 3)
	removeDuplicates(words2);
	printList(words2);

	// check findMinimum
	char* minimum_word = findMinimum(words2);
	cout << minimum_word << endl;

	// check findWordSequence
	int start, end;
	char words3[MAX_WORD][MAX_WORD_SIZE] = { "and", "finish", "soon" };
	findWordSequence(words1, words3, start, end);

	cout << start << " " << end << endl;
	return 0;
	

}

void printList(char words[][MAX_WORD_SIZE])
{
	for (int i = 0; i < MAX_WORD && words[i][0] != 0; i++)
	{
		if (words[i][0] != 0)
			cout << words[i] << " ";
	}
	cout << endl;
}


int numOfWords(const char words[][MAX_WORD_SIZE])
{
	int count = 0;
	for (int i = 0; i != MAX_WORD; i++)
	if (words[i][0] != 0)
		count++;
	return count;
}


void initialize(char words[][MAX_WORD_SIZE], const char str[], char delimiter)
{
	int wordsPos = 0;
	int wordsCharPos = 0;
	for (int strPos = 0; str[strPos] != 0; strPos++)
	{
		if (str[strPos] != delimiter)
		{
			words[wordsPos][wordsCharPos] = str[strPos];
			wordsCharPos++;
		}
		else
		{
			words[wordsPos][wordsCharPos] = 0;
			wordsPos++;
			wordsCharPos = 0;
		}
	}
	words[wordsPos][wordsCharPos] = 0;		//if there is no delimiter after the last character, the else statement does not add the zero byte to the end of the cstring
	for (int i = wordsPos + 1; i != MAX_WORD; i++)	//in case the array is just declared and not initialized, so the nonfilled elements do not have a zero byte in them
		words[i][0] = 0;
}


int findWord(char words[][MAX_WORD_SIZE], const char str[])
{
	for (int i = 0; i != MAX_WORD; i++)
	{
		if (0 == strcmp(words[i], str))
			return i;
	}
	return -1;
}


void removeWord(char words[][MAX_WORD_SIZE], unsigned int i)
{

	int numentries = -1;
	for (int k = 0; (k != MAX_WORD); k++)
	{
		if (words[k][0] == 0)
		{
			numentries = k;
			break;
		}
	}
	if (i >= numentries)
		strcpy(words[numentries - 1], "");
	else
	{
		for (int j = i; j != numentries - 1; j++)
		{
			strcpy(words[j], words[j + 1]);
		}
		strcpy(words[numentries - 1], "");
	}
}


void findWordSequence(char words1[][MAX_WORD_SIZE], const char words2[][MAX_WORD_SIZE], int& start, int& end)
{
	int traverse1 = 0;
	int traverse2 = 0;
	bool firstfound = false;
	for (; traverse1 != MAX_WORD; traverse1++)
	{
		if (0 == strcmp(words2[traverse2], words1[traverse1]))
		{
			if (!firstfound)
			{
				start = traverse1;
				firstfound = true;
			}
			if ((traverse2 + 1 == MAX_WORD) || words2[traverse2 + 1][0] == 0)
			{
				end = traverse1;
				return;
			}
			traverse2++;
		}
	}
	start = -1;
	end = -1;
}


int insertWord(char words[][MAX_WORD_SIZE], const char new_word[], int i)	//doesnt work yet, runtime error
{
	int lastindex = -1;
	for (int k = 0; (k != MAX_WORD); k++)
	{
		if (words[k][0] == 0)
		{
			lastindex = k;
			break;
		}
	}
	if (lastindex == -1)
		return -1;
	if (i >= lastindex)
	{
		strcpy(words[lastindex], new_word);
		return lastindex;
	}
	for (int j = lastindex; j != i; j--)
	{
		strcpy(words[j], words[j - 1]);
	}
	strcpy(words[i], new_word);
	return i;
}


char* findMinimum(char words[][MAX_WORD_SIZE])
{
	char temporaryArr[MAX_WORD][MAX_WORD_SIZE] = {};
	for (int k = 0; (!strcmp(words[k], "")) || k != MAX_WORD; k++)
	for (int h = 0; h != strlen(words[k]); h++)
		temporaryArr[k][h] = words[k][h];

	for (int i = 0; (i != MAX_WORD) || (!strcmp(temporaryArr[i], "")); i++)
	for (int j = 0; j != strlen(temporaryArr[i]); j++)
	if (temporaryArr[i][j] >= 'A' && temporaryArr[i][j] <= 'Z')
		temporaryArr[i][j] = char(int(temporaryArr[i][j]) + int(int('a') - int('A')));

	int smallestIndex = 0;
	for (int a = 0; (strcmp(temporaryArr[a], "")) && a != MAX_WORD; a++)
	{

		if (!(-1 == strcmp(temporaryArr[smallestIndex], temporaryArr[a])) &&	//test function for a maxsize filled up
			!(0 == strcmp(temporaryArr[smallestIndex], temporaryArr[a])))
			smallestIndex = a;
	}
	return words[smallestIndex];
}


int removeDuplicates(char words[][MAX_WORD_SIZE])
{
	int duplicate_count = 0;
	int numentries = -1;
	for (int k = 0; (k != MAX_WORD); k++)
	{
		if (words[k][0] == 0)
		{
			numentries = k;
			break;
		}
	}

	for (int i = 0; i != numentries; i++)
	{
		for (int j = i + 1; j != numentries; j++)
		{
			if (!strcmp(words[i], words[j]))
			{
				strcpy(words[j], "remove");
			}
		}
	}

	for (int i = 0; i != numentries; i++)
	if (!strcmp(words[i], "remove"))
		duplicate_count++;

	for (int i = 0; i != numentries; i++)
	if (!strcmp(words[i], "remove"))
	{
		removeWord(words, i);
		i--;
	}

	return duplicate_count;
}


int removeAllInstances(char words[][MAX_WORD_SIZE], const char str[])
{
	int removed_count = 0;
	for (int i = 0; words[i][0] != 0; i++)
	if (!strcmp(words[i], str))
	{
		removeWord(words, i);
		removed_count++;
	}
	return removed_count;
}



/*
// output for the example main
7
orange apple orange pear melon apple mango
orange apple orange pear grape melon apple mango
we are working on project 3 of course CS31 and we will finish it soon
4
we are working on 3 of course CS31 and we will finish it soon
2
are working on 3 of course CS31 and will finish it soon
orange apple pear grape melon mango
apple
7 11

*/