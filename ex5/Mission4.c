
#include <stdio.h>
#include <malloc.h>
#include "Mission4.h"

/******************************************************************************
* Function name: Mission4
* Input:
* Output: void
* Operation function: the function get a number of chars to allocate and checks
* if the aloccation succeded. Then, it gets a string and a number n, and reverse
* the first n words.
* For Example: "Look at this young man", 4 -> "young this at Look man"
* Note: If n is 0 or 1, nothing happens
* *****************************************************************************/

void Mission4()
{
	//Variables Delceration
	int n, size1, length = 1;
	char dummy;
	char *p1;
	//End of Variables Delceration

	//get amount of chars to allocate
	printf("Please enter how many chars to allocate:\n");
	scanf("%d", &size1);
	//catch the '\n' with dummy
	scanf("%c", &dummy);

	//allocate memory for the string
	p1 = (char *)malloc(size1*sizeof(char));

	//check if the memory allocation succeded
	if ((p1 == NULL))
	{
		printf("Error: Cannot allocate Memory\n");
		return;
	}
	printf("Allocated %d chars\n", size1);

	//get string and number, and reverse the words according to the number
	printf("Please enter your string:\n");
	fgets(p1, size1, stdin);
	
	printf("Please enter how many words to reverse:\n");
	scanf("%d", &n);
	DeleteEnter(p1);
	if ((n == 0) || (n == 1))
	{
		printf("The string after reverse is: ");
		printf("%s\n", p1);
	}
	else
		ReverseNumWords(p1, n);
	free(p1);

}

/******************************************************************************
* Function name: ReverseNumWords
* Input: char *str (The sentence we want to reverse), int n (words to reverse)
* Output: void
* Operation function: place pointer at the word after the n words, and a pointer
* at the end of the previous word. Then reduce the pointer until it reach the
* start of the sentence, and print the word when a space appears. Then print
* the other words (with the first pointer).
* For Example: "Look at this young man", 4 -> "young this at Look man"
* Note: If n is 0 or 1, nothing happens
* *****************************************************************************/

void ReverseNumWords(char *str, int n)
{
	int letters, i;
	char *p2, *p3;
	//if the words to reverse are bigger than exist words
	if (n > CountWords(str))
	{
		printf("Error: Illegal input\n");
		return;
	}
	else
	{
		//get the sum of the letters in the first 'n' words, including ' ' and '\n' 
		letters = CountLetters(str, n);
		//place pointers in the next word, and in the end of the previous word 
		p2 = str + letters;
		p3 = p2 - 2;

		//print the first n words after reverse
		PrintSentence(str, p3);

		//print the other words of the sentence (if exist)
		if (p2[0] != 0)
			printf(" %s", p2);
	}
	//Release p2 and p3
	p3 = NULL;
	p2 = NULL;
	printf("\n");
}

/******************************************************************************
* Function name: CountLetters
* Input: char *str (The sentence we want to reverse), int n (words to reverse)
* Output: The letters (including space and '\n' in the first 'n' words
* Operation function: Run over the chars and count them. The function ends after
* 'n' spaces (' ' or '\n') appeared, which means that 'n' ward passed up.
* If the function reach the end of the sentence before 'n' space shwoed up - it
* means 'n' is bigger than the words in the sentence.
* For Example: "Look at this young man", n=2 -> returns 8
* Note: If n is bigger than the words in the sentence - returns 0.
* *****************************************************************************/
int CountLetters(char *str, int n)
{
	int letters = 0;
	int spaces = 0;
	int i;

	for (i = 0; spaces != n; i++)
	{
		//if hasn't count yet n spaces, and '\0' appeared, so n>sentence's words
		if (str[i] == '\0')
			return letters;

		//counting letters and spaces
		letters++;

		//counting spaces
		if ((str[i] == ' ') || (str[i] == '\n'))
			spaces++;
	}
	return letters;
}

/******************************************************************************
* Function name: PrintWord
* Input: char *str (a sentence that includes a word we want to print)
* Output: void
* Operation function: Print each char until ' ' or '\n' shows up.
* For Example: "Look at this young man" -> "Look"
* Note:
* *****************************************************************************/
void PrintWord(char *p2)
{
	int i = 0;
	int flag = 1;
	while (flag)
	{
		//if space appear - turns flag to 0 and does nothing
		if ((p2[i] == ' ') || (p2[i] == '\n') || (p2[i] == '\0'))
		{
			flag = 0;
			continue;
		}
		printf("%c", p2[i]);
		i++;
	}
}

/******************************************************************************
* Function name: DeleteEnter
* Input: char *str (The sentence)
* Output: void
* Operation function: The function replace '\n' with '\0'
* For Example:
* Note:
* *****************************************************************************/
void DeleteEnter(char *str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
	if (str[i] == '\n')
		str[i] = '\0';
}

/******************************************************************************
* Function name: CountWords
* Input: char *str (The sentence)
* Output: the number of the words in the sentence
* Operation function: The function counts the number of the words in the
* sentence by looking on it's spaces.
* For Example: "Look at this young man" -> 5
* Note: a. Contains at least 1 char.
* b. According to Priel, each word is seperated by 1 space only
* *****************************************************************************/
int CountWords(char *str)
{
	int i, words = 1, isSpace = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			//in case the space appeared after another space, we don't count it
			if (isSpace == 0)
			//in case the sentence start with space, we don't want to count it
			if (i != 0)
				//in case the sentence finish with space, we don't want to count it
			if (str[i + 1] != '\0')
				words++;
			isSpace = 1;
		}
		else
			isSpace = 0;
	}
	return words;
}

/******************************************************************************
* Function name: PrintSentence
* Input: char *str (The sentence), char *ptr(Pointer to after N words)
* Output: 
* Operation function: The function reduce the pointer until space showed,
* and then print the word. After that, it prints the first word.
* For Example: "Look at this young man", 2 -> "Look at"
* Note:
* *****************************************************************************/
void PrintSentence(char *str, char *ptr)
{
	printf("The string after reverse is: ");
	//runs until the pointer point to the start of the sentence
	while (ptr != str)
	{
		//if ' ' appeared, we print the word the comes afer the space
		if ((ptr[0] == ' '))
		{
			PrintWord((ptr + 1));
			printf(" ");
		}
		ptr--;
	}
	//print first word (wasn't printed before because no space comes before it) 
	PrintWord(str);

}