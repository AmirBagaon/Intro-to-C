
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "Mission2.h"
#include "Mission3.h"

/******************************************************************************
* Function name: Mission3
* Input:
* Output: void
* Operation function: the function get a number of chars to allocate and checks
* if the aloccation succeded. Then, it gets a string and print the shortest
* prefix (combination of consecutive letters) that build the string, and the
* length of it.
* For Example: for "abcabc" -> func print "abc" and 3. for "abcde" -> func print
* 'abcde' and 5.
* Note:
* *****************************************************************************/
void Mission3()
{
	//Variables Delceration
	char dummy;
	char *p1, *p2;
	int size1, length, check = 0;
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

	//get string and find its shortest prefix length
	printf("Please enter your string:\n");
	scanf("%s", p1);
	length=ShortestStr(p1);

	//find the shortest prefix
	p2 = LastLetter(p1);
	p2 -= length - 1;
	printf("The shortest prefix building the string is: %s of length %d\n", p2, length);
	
	//free the allocated memory
	p2 = NULL;
	free(p1);
}

/******************************************************************************
* Function name: ShortestStr
* Input: char *str (The string that we look for prefix in it)
* Output: void
* Operation function: Find the Shortest prefix and calculate the times it build
* the string.
* The function place a pointer on the last letter of the string and activates
* the function SubGenerator (from previous mission). If SubGenrator returns 1,
* we found our prefix, else the pointer goes to the previous letter. The
* function continues until SubGenrator reutrns 1 or tunil the end of the string
* For Example: abcabc-> prefix: abc, length:3
* Note: The function use SubGenrator function from previous mission
* *****************************************************************************/
int ShortestStr(char *str)
{
	char* p2;
	//length= prefix's length, flag= 0 if no prefix found yet
	int length = 1, flag = 0;

	//find last letter
	p2 = LastLetter(str);

	//As long as the "flag" is 0, we keep looking for prefix
	while (!flag)
	{
		//if we found prefix - flag is 1
		if ((SubGenerator(str, p2)))
			flag = 1;
		else
		{
			//if no prefix found, pointer goes to previous letter
			p2--;
			length++;
		}
	}
	return length;
}

/******************************************************************************
* Function name: LastLetter
* Input: char *str (The string that we look for prefix in it)
* Output: a pointer to the last letter of she string
* Operation function: Gets a string and returns a pointer to it's last letter.
* For Example: abcde-> returns pointer to 'e'
* Note:
* *****************************************************************************/
char *LastLetter(char *p1)
{
	int length = strlen(p1);
	if (length > 0)
		return (p1 + length - 1);
	else
		return p1;
}
