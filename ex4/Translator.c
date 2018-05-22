
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "Translator.h"

#define SENTENCE_SIZE 52
#define WORD_SIZE 25

/*
We use 3 global variables:
char sentence[]: The sentence that will be send to tokanizer function
int senIndicator: The indicator of the sentence (also will be send to tokanizer)
int endFlag: a "flag" that will be 0 if it is the end of the sentence
*/
char sentence[SENTENCE_SIZE];
int senIndicator;
int endFlag;


/******************************************************************************
* Function name: Translator
* Input:
* Output: void
* Operation function: the function get a sentence and translate it to pig latin.
* Rules: if there is a vowel at start of the word, it print the original
* word+"way". else, all the letters before the frist vowel will come at the 
* end of word, with addition of "ay". if there are no vowel, it print the 
* original word+"ay". In addition, all the letters are lower letters.
*
* For Example: for the sentence: "Amir is great" --> "amirway isway eatgray"
* Note: y is treated as a vowel only if it isn't at the start of the word.
* sentence length may be up to 50.
* *****************************************************************************/
void Translator()
{
	//Variables Delceration
	char word[WORD_SIZE];
	char dummy, answer;
	//End of Variables Delceration
	
	do
	{
		//get a sentence
		printf("Please enter a sentence in English:\n");
		fgets(sentence, SENTENCE_SIZE, stdin);

		//Convert Capital letters to lower letters
		Capitals(sentence);
		//Split the first word from the sentence
		Tokanizer(sentence, word);

		//Set flag to 1. if it is 0 - it's the end of the sentence
		endFlag = 1;
		while (endFlag != 0)
		{
			//Call VowelOrNot to work on the word, and split the next word
			VowelOrNot(word);
			Tokanizer(NULL, word);
		}

		//Get y/n for another sentence, and use dummy to catch '\n'
		printf("\nDo you want to translate another sentence?(y/n)\n");
		scanf("%c", &answer);
		scanf("%c", &dummy);
	} while (answer == 'y'); //end of do-while loop

}

/******************************************************************************
* Function name: Capitals
* Input: char str[SENTENCE_SIZE]
* Output: void
* Operation function: the function convert Capital letters to lower letters
* Note:
* *****************************************************************************/
void Capitals(char str[SENTENCE_SIZE])
{
	char capital = 'a' - 'A';
	int i;
	//Convert Capital letters to lower letters
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] >= 'A') && (str[i] <= 'Z'))
			str[i] += capital;
	}
}


/******************************************************************************
* Function name: Replacer
* Input: char str[WORD_SIZE]]
* Output: void
* Operation function: the function creat new word that starts with the first
* vowel of the word, and place the previous letters in the end of the word.
* Then it add "ay" to the end of the word. If the word dosen't contain vowels,
* it just add "ay" to the end of the word.
* Note: The word that the function got, starts with non-vowel letter.
* If the first letter is '\0', the function do nothing.
* *****************************************************************************/
void Replacer(char str[WORD_SIZE])
{
	//If the first letter is '\0', the function do nothing
	if (str[0] == 0)
		return;

	//set array of chars that will come first, and for chars that will be after
	char before[WORD_SIZE] = "";
	char after[WORD_SIZE] = "";
	int i;
	//set indicators for the 2 arrays and a "flag"
	int flag = 0, placeBefore = 0, placeAfter = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		//if the letter is a vowel, we raise a "flag"
		if (CheckVowel(str[i]))
			flag = 1;

		//if y appear not at the word's start, we raise a "flag"
		if ((str[i]) == 'y')
			if (i != 0)
				flag = 1;

		//if flag is 0, we save the letter in the array "before"
		if (!flag)
		{
			before[placeBefore] = str[i];
			placeBefore++;
		}
		//if flag is 1, we save the letter in the array "after"
		else
		{
			after[placeAfter] = str[i];
			placeAfter++;
		}
	}
	//put '\0' to close the words
	before[placeBefore] = 0;
	after[placeAfter] = 0;

	//print new word: first vowel until end, then the previous letters, then ay
	printf("%s%say ", after, before);
}

/******************************************************************************
* Function name: VowelOrNot
* Input: char word[WORD_SIZE]
* Output: void
* Operation function: the function check if the first letter of the word is a
* vowel or not. if vowel, it add "way" to the word. else, it call Replacer
* function
* Note:
* *****************************************************************************/
void VowelOrNot(char word[WORD_SIZE])
{
	if (CheckVowel(word[0]))
		printf("%sway ", word);
	else Replacer(word);

}

/******************************************************************************
* Function name: CheckVowel
* Input: char ch
* Output: 1 or 0
* Operation function: the function returns 1 if ch is a vowel (a,e,i,o,u),
* and else returns 0.
* Note: '\n' will appear only in the end of the sentence
* *****************************************************************************/
int CheckVowel(char ch)
{
	if ((ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u'))
		return 1;
	return 0;
}

/******************************************************************************
* Function name: WordFinisher
* Input: char sentence[SENTENCE_SIZE]
* Output: void
* Operation function: the function get a sentence (char[]) and put '\0' instead
* of '\n'
* Note: '\n' will appear only in the end of the sentence
* *****************************************************************************/
void WordFinisher(char sentence[SENTENCE_SIZE])
{
	int i;
	for (i = 0; sentence[i] != '\0'; i++)
	{
		if (sentence[i] == '\n')
			sentence[i] = '\0';
	}
}

/******************************************************************************
* Function name: Tokanizer
* Input: char newSentence[SENTENCE_SIZE], char word[WORD_SIZE]
* Output: void
* Operation function: The function "breaks" the sentence into words. each word
* is sperated by a kind of space (' ', '\t', '\n').
* For example: For the sentence: bamba is super great -> bamba. Next time, if
* the variable "newSentence" is Null -> is. etc.
* Note: if newSentence is NULL, the function will work on the previous sentence 
* that has been sent to it.
* *****************************************************************************/
void Tokanizer(char newSentence[SENTENCE_SIZE], char word[WORD_SIZE])
{
	//If there's a new sentence, it works on it. Else, on the previous sentence.
	if (newSentence != NULL)
	{
		//copy the new sentence to the golobal variable "sentence"
		strcpy(sentence, newSentence);
		//restart the indicator
		senIndicator = 0;
	}

	int i;
	//set an indicator for word's array
	int place = 0;
	
	//As long as no kind of space appeared
	while ((IsSpace(sentence[senIndicator])) == 0)
	{
		//Stores the char in word array and raise indicators
		word[place] = sentence[senIndicator];
		place++;
		senIndicator++;
	}
	//If it's the end of the sentence, we turn the "flag" down
	if (sentence[senIndicator] == '\0')
		endFlag = 0;

	//put \0 in end to close the char[], and raise indicator to skip the space
	word[place] = 0;
	senIndicator++;
}

/******************************************************************************
* Function name: IsSpace
* Input: char c
* Output: 1 or 0
* Operation function: The function return 1 if the char c is a kind of space
* (' ', '\t', '\n', '\v','\f', '\0', '\r').
* Note: if newSentence is NULL, the function will work on the previous sentence
* that has been sent to it.
* *****************************************************************************/
int IsSpace(char c)
{
	switch (c)
	{

		//if the char is any kind of space, it will return 1. Else - 0.
	case ' ':
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case '\0':
		return 1;

	default:
		return 0;
	}
}



