
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gadt.h"

//length of the string
#define MAX 15

//function decleration
ELM CreatePoint();
ELM CreateString();
void CpyPoint(ELM s1, ELM s2);
void CpyString(ELM s1, ELM s2);
int CmpPoint(ELM e1, ELM e2);
int CmpString(ELM e1, ELM e2);
void PrintPoint(ELM e1);
void PrintString(ELM e1);
void FreePoint(ELM *p1);
void FreeString(ELM *p1);
ELM AttachPoint(ELM e1, ELM e2);
ELM AttachString(ELM e1, ELM e2);
void DeleteEnter(char *str);
//end of function decleration

//Build struct of point
typedef struct point_s
{
	int x, y;
} point;


/******************************************************************************
* Function name: CreateString()
* Input: 
* Output: returns pointer to allocation for string with the length of MAX (15)
* Operation function: Allocates memory and return pointer to it.
* For Example:
* Note:
* *****************************************************************************/
ELM CreateString()
{
	return (char *)malloc(MAX*sizeof(char));
}
/******************************************************************************
* Function name: CreatePoint()
* Input:
* Output: returns pointer to allocation for point
* Operation function: Allocates memory and return pointer to it.
* For Example:
* Note:
* *****************************************************************************/
ELM CreatePoint()
{
	return (point*)malloc(sizeof(point));
}

/******************************************************************************
* Function name: CpyPoint
* Input: ELM p1, ELM p2 (2 elements, in our case - point)
* Output: void
* Operation function: copy the value of p2 to p1.
* For Example:
* Note:
* *****************************************************************************/

void CpyPoint(ELM p1, ELM p2)
{
	point* temp1 = (point*)p1;
	point* temp2 = (point*)p2;
	temp1->x = temp2->x;
	temp1->y = temp2->y;
}

/******************************************************************************
* Function name: CpyString
* Input: ELM s1, ELM s2 (2 elements, in our case - string)
* Output: void
* Operation function: copy the value of s2 to s1.
* For Example:
* Note:
* *****************************************************************************/
void CpyString(ELM s1, ELM s2)
{
	strcpy((char *)s1, (char *)s2);	
}

/******************************************************************************
* Function name: CmpPoint
* Input: ELM e1, ELM e2 (2 elements, in our case - point)
* Output: void
* Operation function: Compare between the elements and return 1 if e1 is bigger,
* 0 if equal, and -1 if e2 is bigger.
* For Example:
* Note:
* *****************************************************************************/
int CmpPoint(ELM e1, ELM e2)
{
	point* p1 = (point*)e1;
	point* p2 = (point*)e2;

	//calculate the distance
	int d1, d2;
	d1 = abs(p1->x) + abs(p1->y);
	d2 = abs(p2->x) + abs(p2->y);

	if (d1 > d2)
		return 1;
	else if (d1 < d2)
	return -1;
	else return 0;
}
/******************************************************************************
* Function name: CmpString
* Input: ELM s1, ELM s2 (2 elements, in our case - string)
* Output: void
* Operation function: Compare between the elements and return 1 if s1 is bigger,
* 0 if equal, and -1 if s2 is bigger.
* For Example:
* Note:
* *****************************************************************************/
int CmpString(ELM s1, ELM s2)
{
	return strcmp((char *)s1, (char *)s2);
}

/******************************************************************************
* Function name: PrintPoint
* Input: ELM e1 (in our case - point)
* Output: void
* Operation function: Print the point in special way
* For Example: (2,3)--> 002|003
* Note:
* *****************************************************************************/
void PrintPoint(ELM e1)
{
	point* p = (point*)e1;
	printf("%.3d|%.3d\n", p->x, p->y);
}
/******************************************************************************
* Function name: PrintString
* Input: ELM e1 (in our case - String)
* Output: void
* Operation function: Print the string
* For Example:
* Note:
* *****************************************************************************/
void PrintString(ELM str)
{
	printf("%s\n", (char *)str);
}

/******************************************************************************
* Function name: FreePoint
* Input: ELM e1 (in our case - point)
* Output: void
* Operation function: Free the point allocation
* For Example:
* Note:
* *****************************************************************************/
void FreePoint(ELM *p1)
{
	free((point*)p1);
}
/******************************************************************************
* Function name: FreeString
* Input: ELM e1 (in our case - String)
* Output: void
* Operation function: Free the string allocation
* For Example:
* Note:
* *****************************************************************************/
void FreeString(ELM *s1)
{
	free((char*)s1);
}

/******************************************************************************
* Function name: AttachPoint (add_elm_to_elm)
* Input: ELM e1, ELM e2 (2 elements, in our case - point)
* Output: void
* Operation function: Add point's value to other point
* For Example:
* Note:
* *****************************************************************************/
ELM AttachPoint(ELM e1, ELM e2)
{
	point* p1 = (point*)e1;
	point* p2 = (point*)e2;

	p1->x += p2->x;
	p1->y += p2->y;

	return p1;
}
/******************************************************************************
* Function name: AttachString (add_elm_to_elm)
* Input: ELM e1, ELM e2 (2 elements, in our case - String)
* Output: void
* Operation function: Attach to string together (add a string to a string)
* For Example:
* Note:
* *****************************************************************************/
ELM AttachString(ELM s1, ELM s2)
{
	strcat((char*)s1, (char*)s2);
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

int main()
{
	RESULT r = success;
	HEAD head1;
	int program;
	point p,p2;
	char choice = 'b', dummy;
	char str[MAX], str2[MAX];

	scanf("%d", &program);
	scanf("%c", &dummy);
	//if 1 was insert, creat list of points and get a point
	if (program)
	{
		
		scanf(" (%d,%d)", &p.x, &p.y);
		head1= SLCreate(&p, CreatePoint, CpyPoint, CmpPoint, FreePoint, PrintPoint, AttachPoint);
		scanf("%c", &dummy);
	}
	else
	{
		//if 0 was insert, creat list of strings and get a string
		fgets(str, MAX, stdin);
		DeleteEnter(str);
		head1 = SLCreate(str, CreateString, CpyString, CmpString, FreeString, PrintString, AttachString);
	}

	while (choice != 'e')
	{
		//get an opperation	
		scanf("%c", &choice);
		scanf("%c", &dummy);
		
		switch (choice)
		{
		//Case 'a' - add point/string to the list
		case 'a':
			if (program)
			{
				//add a point to the list
				scanf(" (%d,%d)", &p.x, &p.y);
				scanf("%c", &dummy);
				SLAddListElement(&head1, &p);
			}
			else
			{
				//add a string to the list
				fgets(str, MAX, stdin);
				DeleteEnter(str);
				SLAddListElement(&head1, str);
			}
		break;

		case 's':
			//Case 's' - check if point/string is in the list
			if (program)
			{
				//check if point is in the list
				scanf(" (%d,%d)", &p.x, &p.y);
				scanf("%c", &dummy);
				if ((SLFindElement(head1, &p) != NULL))
					printf("TRUE\n");
				else
					printf("False\n");
			}
			else
			{	
				//check if string is in the list
				fgets(str, MAX, stdin);
				DeleteEnter(str);
				if ((SLFindElement(head1, str) != NULL))
					printf("TRUE\n");
				else
					printf("False\n");
			}
			break;

			//Case 'd' - remove point/string from the list
		case 'd':
			if (program)
			{
				//remove point from the list
				scanf(" (%d,%d)", &p.x, &p.y);
				scanf("%c", &dummy);
				r = SLRemoveElement(&head1, &p);
			}
			else
			{
				//remove string from the list
				fgets(str, MAX, stdin);
				DeleteEnter(str);
				r = SLRemoveElement(&head1, str);
			}

			//if there was only one element: set choice as 'e' to finish program	
			if (r == failure)
				choice='e';


		break;
		//Case 'p' - print all point/string in the list
		case 'p':
			if (program)
				SLPrintElements(head1);
			else
				SLPrintElements(head1);
			break;

		//Case 'l' - print the list's length
		case 'l':
			printf("%d\n", SLSize(head1));
		break;

		//Case 't' - add point/string to another point/string in the list
		case 't':
			if (program)
			{
				//scan 2 points and check if the first point is in the list
					scanf(" (%d,%d) (%d,%d)", &p.x, &p.y, &p2.x, &p2.y);
					scanf("%c", &dummy);
					if ((SLFindElement(head1, &p) != NULL))
						//add the 2nd point to the appropriate point in the list
						SLAddElmToElm(&head1, &p, &p2);
			}
			else
			{
				//scan 2 strings and check if the first string is in the list
				scanf(" %s %s", str, str2);
				scanf("%c", &dummy);
				if ((SLFindElement(head1, str) != NULL))
					//add the string to the string in the list
					SLAddElmToElm(&head1, str, str2);
			}
			break;
		break;
		//Case 'e' - destroy the list (free all values and nodes in it)
		case 'e':
			SLDestroy(head1);
		break;
		default:

		break;
		}
	}
return 0;
}