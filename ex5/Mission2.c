
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Mission2.h"

/******************************************************************************
* Function name: Mission2
* Input:
* Output: void
* Operation function: Get 2 numbers seperated by space for allocation. Check if
* allocation succeded. Then get 2 appropriate strings ('str' and 'sub').
* The function calculateand print how many times 'sub' build 'str'.
* For Example: 'str'=abcabcabcabc, 'sub'=abc -> abc build abcabcabcabc 4 times,
* so the function will print: "abcabcabcabc is a concatenation of abc 4 times".
* Another Example: 'str'=abcabccabcab, 'sub'=abc. 'sub' doesn't build 'str', so
* the function print: "No concatenation found".
* Note:
* *****************************************************************************/
void Mission2()
{
	//Variables Delceration
	int size1, size2, count;
	char dummy;
	char *p1, *p2;
	//End of Variables Delceration

	//get amount of chars to allocate
	printf("Please enter how many chars to allocate to the two strings:\n");
	scanf("%d %d", &size1, &size2);
	//catch the '\n' with dummy
	scanf("%c", &dummy);

	//allocate memory for the strings
	p1 = (char *)malloc(size1*sizeof(char));
	p2 = (char *)malloc(size2*sizeof(char));

	//check if the memory allocation succeded
	if ((p1 == NULL) || (p2 == NULL))
	{
		printf("Error: Cannot allocate Memory\n");
		return;
	}
	printf("Allocated %d chars and %d chars\n", size1, size2);
	// get 2 strings
	printf("Please enter two arrays of chars:\n");
	scanf("%s %s", p1, p2);

	//Calculate how many times p2 build p1 and print it
	count = SubGenerator(p1, p2);
	if (!count)
		printf("No concatenation found\n");
	else
		printf("%s is a concatenation of %s %d times\n", p1, p2, count);

	//free the allocated memory
	free(p1);
	free(p2);
}

/******************************************************************************
* Function name: SubGenerator
* Input: char *str, char *sub ('str' is the prime string, 'sub' might build it)
* Output: an int of the times 'sub' is a concatenation of 'str' 
* Operation function: Check and print how many times 'sub' is a concatenation
* of 'str'.
* The function compare each letter. If the letters not equal, return 0. Else, it
* counts each time all of 'sub' is in 'str', and returns it.
* For Example: 'str'= abc, 'sub'=a -> 0 (because a!=b).
* 'str'=abab, 'sub'=ab -> 2 (because all of 'sub' is 2 times in 'str')
* Note:
* *****************************************************************************/
int SubGenerator(char *str, char *sub)
{
	int i = 0;
	int count = 0;
	int length1 = strlen(str);
	int length2 = strlen(sub);

	//if length1%length2 !=0, we learn that sub isn't concatenation of str
	if (((length1%length2) != 0) || (length2>length1))
		return 0;

	for (i = 0; i < length1; i++)
	{
		//compare the letters. If not equals - sub isn't concatenation of str
		if (str[i] == sub[(i%length2)])
			count++;
		else return 0;
	}
	//devide the equal letters by sub's length to know the times sub is in str
	count = count / length2;
	return count;
}
