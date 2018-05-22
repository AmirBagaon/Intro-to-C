
#include <stdio.h>
#include <string.h>
#include <malloc.h> 
#include "Mission5.h"


/******************************************************************************
* Function name: Mission5
* Input:
* Output: void
* Operation function: the function get names until 'QUIT' shows up. Then it
* print the names sorted from a-z.
* For Example: "yonatan", "yair", "amir", "moshe" "QUIT" -> "amir", "moshe",
* "yair", "yonatan".
* Note:
* *****************************************************************************/
void Mission5()
{
	//Variables Delceration
	char *sentence, *word=NULL;
	int count = 0, flag = 1, check;
	char dummy;
	//End of Variables Delceration

	//catch the '\n' with dummy
	scanf("%c", &dummy);

	//allocate memory for the sentence
	sentence = (char *)malloc(1 * sizeof(char));
	if ((AllocFailed(sentence)))
		return;
	sentence[0] = 0;

	printf("Please enter list of names:\n");
	do
	{
		//get a word from user and check if allocation is ok
		word=GetWord(word);
		if (AllocFailed(word))
		{
			free(sentence);
			return;
		}
		
		//if the word isn't QUIT - add the word to the sentence + space
		if ((strcmp(word, "QUIT") != 0))
		{
			sentence = Attach(sentence, word);
			if (AllocFailed(sentence))
			{
				free(word);
				return;
			}
			//count the word as a name
			count++;
		}
		else
			//else, turn flag to 0 and quit the loop
			flag = 0;
	} while (flag);

	//free the allocated memory of the last word
	free(word);

	printf("There are %d names:\n",count);
	//sort the words (And quit if allocation failed)
	if (count != 0)
	{
		check=SortNames(sentence);
		if (check == 0)
			return;
	}
	//free the allocated memory of the sentence
	free(sentence);
}

/******************************************************************************
* Function name: Attach
* Input: char *sentence, char *word (Two strings we want to attach together)
* Output: a pointer to string that was built from the two strings
* Operation function: Get 2 strings, then allocates memory for a string in
* the length of the both strings, and add them together. Then, return a pointer
* to this string
* For Example: "Hi" "There! -> "HiThere!"
* Note:
* *****************************************************************************/
char *Attach(char *sentence, char *word)
{
	int length;
	char *s;
	if (sentence != NULL)
		length = strlen(sentence);
	
	//Calculate the length
	length += strlen(word) + 1 * sizeof(char);
	
	//allocate memory for the new string
	s = realloc(sentence, (length+1)*sizeof(char));
	if (AllocFailed(s))
		return NULL;

	strcat(s, word);
	strcat(s, " ");
	return s;
}

/******************************************************************************
* Function name: SortNames
* Input: char *sentence (The string with the names we want to sort)
* Output: void
* Operation function: Get a string with names and sort it.
* The function Copy the string to a temp string. After that, it cut the temp  
* string to words with strtok, and find and print the minimum word.
* Then, in the original string, change the first letter of the minimal word to
* a char that is bigger than any lower letter. Then copy it to the temp string,
* and find minimal - until all words begins with that char.
* For Example: "moshe", "omer", "evyatar" -> "evyatar", "moshe", "omer"
* Note: All the names will contain lower letters only.
* *****************************************************************************/
int SortNames(char *sentence)
{
	char *token, *minimum, *temp;
	int flag = 1, place, minPlace;

	//allocate memory for temp string and copy the original string to it
	temp = malloc((strlen(sentence) + 1)*sizeof(char));
	if (AllocFailed(temp))
		return 0;
	strcpy(temp, sentence);
	
	//run as long as flag=1
	while (flag)
	{
		place = 0;
		minPlace = 0;

		//cut the temp string to words with strtok
		token = strtok(temp, " ");
		minimum = token;
		while (token != NULL)
		{
			//find the minimum word and its place
			if (strcmp(minimum, token) > 0)
			{
				minimum = token;
				minPlace = place;
			}
			place += (strlen(token) + 1);
			token = strtok(NULL, " ");
		}

		//if all words begins with a char that > 'z' - turn flag to 0
		if (minimum[0] == ('z' + 1))
		{
			flag = 0;
			minimum = NULL;
			//free the allocated memory
			free(temp);
		}

		//else, change the minimum word in the original sting
		else
		{
			printf("%s\n", minimum);
			//change it to a word that will be bigger than the others
			sentence[minPlace] = 'z' + 1;
			//copy the string to temp, and run the loop again
			strcpy(temp, sentence);
		}
	}
	return 1;
}

/******************************************************************************
* Function name: AllocFailed
* Input: char *sentence (The string that maybe got a allocation)
* Output: 1 if alloc falid, 0 if succeced
* Operation function: Check if the pointer is NULL or not. If it's NULL - the
* allocation wasn't succssesful and return 1. Else returns 0.
* For Example: 
* Note: All the names will contain lower letters only.
* *****************************************************************************/
int AllocFailed(char *ptr)
{
	if (ptr == NULL)
	{
		printf("Error: Cannot allocate Memory\n");
		return 1;
	}
	return 0;

}

/******************************************************************************
* Function name: GetWord
* Input: char *word (The previous word)
* Output: A pointer to allocation with the new word (or NULL if alloc failed)
* Operation function: Free the prvious word. Then alloc memory for 1 char,
* and if theres another char - realloc it by 1 more, until the end of the word.
* For Example:
* Note: Return Null if alloc failed
* *****************************************************************************/

char *GetWord(char *word)
{
	char c;
	int i = 0;
	//free the previous word and allocate memory for new letter
	free(word);
	word = (char *)malloc(1 * sizeof(char));
	if (AllocFailed(word))
		return NULL;

	//get chars until '\n' shows up
	while ((c = getchar()) != '\n')
	{
		word[i] = c;
		i++;
		//allocates memory for another letter
		word = realloc(word, (i + 1)*sizeof(char));
		if (AllocFailed(word))
			return NULL;
	}
	//close the word
	word[i] = '\0';
	return word;
}
