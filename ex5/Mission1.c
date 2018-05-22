
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Mission1.h"

/******************************************************************************
* Function name: Mission1
* Input:
* Output: void
* Operation function: the function get a number of chars to allocate and checks 
* if the aloccation succeded. Then, it gets a string and sort it's lower and 
* capital letters. The sorted lower-letters appears first, and after them the
* sorted capital letters appears.    
* For Example: ZzXxAAAa -> axzAAAXZ. 
* Note: If the string is already sorted, the function do nothing but print:
* "The string is already sorted".
* *****************************************************************************/
void Mission1()
{
	//Variables Delceration
	char *ptr;
	char dummy;
	int size, isSorted;
	//End of Variables Delceration
	
	//get amount of chars to allocate
	printf("Please enter how many chars to allocate:\n");
	scanf("%d", &size);
	//catch the '\n' with dummy
	scanf("%c", &dummy);
	
	//allocate memory for the string
	ptr = (char *)malloc(size*sizeof(char));

	//check if the memory allocation succeded
	if (ptr == NULL)
	{
		printf("Error: Cannot allocate Memory\n");
		return;
	}
	printf("Allocated %d chars\n", size);
	printf("Please enter string to be sorted:\n");

	//get string and check if it is legal
	fgets(ptr, size, stdin);
	if (!(Legal(ptr)))
		return;

	//checks if the string is sorted. If not, it sorts it
	isSorted = SortString(ptr);
	if (isSorted == 0)
		printf("The string is already sorted\n");
	else
		//print the sorted string
		printf("The string after sorting is: %s\n", ptr);

	//free the allocated memory
	free(ptr);
}

/******************************************************************************
* Function name: FlipLetters
* Input: char *str (The string need to be sorted)
* Output: void
* Operation function: Turns lower letters to capital letters, and vice versa
* For Example: ZzXxAAAa -> zZxXaaaA
* Note:
* *****************************************************************************/
void FlipLetters(char *str)
{
	//get the diffrence between 'a' and 'A'
	char diffrence = 'a' - 'A';
	int i = 0;

	//Runs until end of the string
	for (i = 0; str[i] != '\0'; i++)
	{
		// if \'n' appeared - does nothing
		if (str[i] == '\n')
			continue;
		//Turns lower letters to capitals
		if ((str[i] >= 'a') && (str[i] <= 'z'))
			str[i] -= diffrence;
		else
			//Turns capital letters to lower
			str[i] += diffrence;
	}
}

/******************************************************************************
* Function name: Swap
* Input: char *str (The string need to be sorted), int i, int j (2 indicators)
* Output: void
* Operation function: Swap between two values in the String
* For Example: str=Football, i=3, j=4 --> Foobtall
* Note:
* *****************************************************************************/

void Swap(char *str, int i, int j)
{
	char temp;
	temp = str[i];
	str[i] = str[j];
	str[j] = temp;
}

/******************************************************************************
* Function name: SortString
* Input: char *str (The string need to be sorted)
* Output: 1 if it sorted the string, 0 if it was already sorted.
* Operation function: Sort the String to group of sorted lower-letters and group
* of sorted capital letters.
* First, it flip all capitals to lower letters and vice versa (because
* capitals<lowers, but we need the lowers first). Then it sort the string (and
* the result is: CAPITALS-lowers), and then flip again the capitals to lowers
* and vice versa (so the result is lowers-CAPITALS). Then returns 1. If the 
* function didn't need to sory anything - returns 0.
* For Example: str=FooTBall--> BFTalloo (and returns 1). str=footALL -> footALL
* (and returns 0).
* Note:
* *****************************************************************************/

int SortString(char *str)
{
	int size = strlen(str);
	//Change capitals to lower and vice versa
	FlipLetters(str);

	int i, j, tmp;
	int count = 0;
	//go over the string
	for (i = 0; i<size - 1; i++)
		//for each organ, if it is bigger than the next one - then swap 
	for (j = 0; j<size - 1 - i; j++)
		if (str[j]>str[j + 1])
			
		{
			Swap(str, j, j + 1);
			count = 1;
		}
	
	//Change capitals to lower and vice versa
	FlipLetters(str);
	return count;
}

/******************************************************************************
* Function name: Legal
* Input: char *str (The string need to be sorted)
* Output: 1 if it has legal chars , 0 otherwise.
* Operation function: check each char if it is legal, between 'a'-'z' or 'A'-'Z'
* If all of them legal, returns 1, else if not, returns 0.
* For Example: Hello2U -> 0. Hello -> 1.
* Note:
* *****************************************************************************/

int Legal(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		// if '\n' appeared - does nothing
		if (str[i] == '\n')
			continue;
		// if the char isn't legal - returns 0
		if (!((str[i] >= 'a'&&str[i] <= 'z') || (str[i] >= 'A'&&str[i] <= 'Z')))
		{
			printf("Error: Illegal input\n");
			return 0;
		}
	}
	return 1;
}