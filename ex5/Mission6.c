
#include <stdio.h>
#include <malloc.h> 
#include "Mission6.h"

//We have global int that indicates the array's size
int arrSize = 0;

/******************************************************************************
* Function name: Mission6
* Input:
* Output: void
* Operation function: the function creat a dynamic queue (FIFO) from an array.
* Options avalible: Add/remove value; Display all value; Print maximum/minimum;
* Find item's index; Clear queue; Print menu again
* For Example: For the input: 1 10 1 30 1 50 2 5 --> The function add 10,30,50
* to the queue, then removes 10, then print the minimum: 30.
* Note:
* *****************************************************************************/
void Mission6()
{
	int choice, check;
	int **queue = (int **)malloc(1* sizeof(int *));
	if (QueueAllocFailed(queue))
		return;
	
	printf("Please select your choice:\n");
	Menu();
	scanf("%d", &choice);

	while (choice != 0)
	{
		//act accordingly the the choice
		switch (choice)
		{
		
		//add number to the queue
		case 1:
			queue = (int **)realloc(queue, (arrSize+1)*sizeof(int *));	
			if (QueueAllocFailed(queue))
				return;
			check=Add(queue);
			//if allocation for new item was failed
			if (!check)
				return;
			break;
		//remove number from the queue
		case 2:
			Remove(queue);
			if (arrSize!=0)
			queue = (int **)realloc(queue, (arrSize)*sizeof(int *));
			if (QueueAllocFailed(queue))
				return;
			break;
		//Display queue
		case 3:
			Display(queue);
			break;
		//Print Maximum
		case 4:
			Maximum(queue);
			break;
		//Print Minimum
		case 5:
			Minimum(queue);
			break;
		//Print item's index
		case 6:
			FindItem(queue);
			break;
		//Clear queue
		case 7:
			Clear(queue);
			printf("Queue is clear\n");
			break;
		//Print menu
		case 8:
			Menu();
			break;
		//In any other input
		default:
			printf("Error: Unrecognized choice\n");
			break;
		} //End of switch

		printf("Please select your next choice (select 8 for complete menu)\n");
		scanf("%d", &choice);
	} //End of while

	if (arrSize!=0)
	//if the queue isn't empty - clears it
	Clear(queue);
	
	//free the allocated memory
	free(queue);
} 

/******************************************************************************
* Function name: Add
* Input: char **queue (The queue)
* Output: 0 if the allocation for new item failed, otherwise 1
* Operation function: get a value and add a pointer in the queue that points to
* the value.
* For Example: if the organs: 10, 30 and we add 50 --> 10, 30, 50 are the organs
* Note:
* *****************************************************************************/
int Add(int **queue)
{
	//increasing the size of the array by 1
	arrSize++;	
	//allocates memory for pointer to point the value
	queue[arrSize-1] = (int *)malloc(sizeof(int));
	if (CellAllocFailed(queue[arrSize - 1]))
		return 0;
	int item;
	printf("Enter item value to add\n");
	scanf("%d", &item);
	//set the pointer to point the value
	*queue[arrSize - 1] = item;
	printf("Item %d added\n", item);
	return 1;
	} 

/******************************************************************************
* Function name: Remove
* Input: char **queue (The queue)
* Output: void
* Operation function: Removes the first organ of the queue.
* For Example: 10 30 50  --> 30 50 
* Note:
* *****************************************************************************/
void Remove(int **queue)
{
	int i, temp;
	//if queue isn't empty
	if (arrSize != 0)
	{

		temp = *queue[0];
		for (i = 0; i < arrSize - 1; i++)
			//every pointer points to the value of the next pointer
			*queue[i] = *queue[i + 1];

		//free the last pointer
			free(queue[arrSize - 1]);
		
		//decrease arrSize by 1
		arrSize--;
		printf("Item %d was removed\n", temp);
	}
	else
		//if queue is already empty
		printf("Error: Queue is empty!\n");
}

/******************************************************************************
* Function name: Clear
* Input: char **queue (The queue)
* Output: void
* Operation function: Clear all the organs of the queue.
* For Example: 10 30 50  --> Empty
* Note:
* *****************************************************************************/
void Clear(int **queue)
{	
	if (arrSize != 0)
	{
		int i;
		//free all organs in the queue
		for (i = 0; i < arrSize; i++)
			free(queue[i]);

		//set the size of the array as 0 (empty array)
		arrSize = 0;
	}
	
}
/******************************************************************************
* Function name: Display
* Input: char **queue (The queue)
* Output: void
* Operation function: Print all the organs of the queue.
* For Example: 10 30 50 are organs  --> Print 10 30 50
* Note:
* *****************************************************************************/
void Display(int **queue)
{
	int i;
	if (arrSize == 0)
		printf("Error: Queue is empty!\n");
	else
	//if queue isn't empty
	{
		printf("Queue items are: ");
		for (i = 0; i < arrSize; i++)
			printf("%d ", *queue[i]);
		printf("\n");
	}
}

/******************************************************************************
* Function name: Maximum
* Input: char **queue (The queue)
* Output: void
* Operation function: Print the maximum of the queue.
* For Example: 10 30 50 are organs  --> Print 50
* Note:
* *****************************************************************************/
void Maximum(int **queue)
{
	if (arrSize == 0)
		printf("Error: Queue is empty!\n");
	else
	//if queue isn't empty
	{
		int i = 0;
		int maximum = *queue[0];
		//find maximum
		for (i = 0; i < arrSize; i++)
		if (*queue[i]>maximum)
			maximum = *queue[i];
		printf("Maximum item in queue is %d\n", maximum);
	}
}
/******************************************************************************
* Function name: Minimum
* Input: char **queue (The queue)
* Output: void
* Operation function: Print the minimum of the queue.
* For Example: 10 30 50 are organs  --> Print 10
* Note:
* *****************************************************************************/
void Minimum(int **queue)
{
	if (arrSize == 0)
		printf("Error: Queue is empty!\n");
	else
	//if queue isn't empty
	{
		int i = 0;
		int minimum = *queue[0];
		//find minimum
		for (i = 0; i < arrSize; i++)
		if (*queue[i] < minimum)
			minimum = *queue[i];
		printf("Minimum item in queue is %d\n", minimum);
	}
}

/******************************************************************************
* Function name: FindItem
* Input: char **queue (The queue)
* Output: void
* Operation function: Get and item from user, check if it is in the queue, 
* and print its index.
* For Example: 10 30 50, item is 30 --> index=2
* Note: Item can apper more then once. The function prints all of its indexes
* *****************************************************************************/
void FindItem(int **queue)
{
	int i, item, index = -1;
	if (arrSize == 0)
		printf("Error: Queue is empty!\n");
	else
	{
	//if queue isn't empty
	printf("Please enter the item you would like to know its index\n");
	scanf("%d", &item);
	for (i = 0; i < arrSize; i++)
	{
		//if item is in the queue - print its index
		if (*queue[i] == item)
		{
			index = i + 1;
			printf("Item %d index is %d\n", item, index);
		}
	}
	if (index == -1)
		//if item isn't in queue
		printf("Error: no such item!\n");
	}
}
/******************************************************************************
* Function name: Menu
* Input:
* Output: void
* Operation function: Print the menu
* For Example:
* Note:
* *****************************************************************************/
void Menu()
{
	printf("0.Exit\n");
	printf("1.Add item to the queue\n");
	printf("2.Remove item from the queue\n");
	printf("3.Print queue\n");
	printf("4.Print the maximum item in the queue\n");
	printf("5.Print the minimum item in the queue\n");
	printf("6.Print index of given item\n");
	printf("7.Clear queue\n");
	printf("8.Print the menu\n");
}

/******************************************************************************
* Function name: CellAllocFailed
* Input: char **ptr (The queue)
* Output: 1 if alloc falid, 0 if succeced
* Operation function: Check if the pointer is NULL or not. If it's NULL - the
* allocation wasn't succssesful and return 1. Else returns 0.
* For Example:
* Note:
* *****************************************************************************/
int QueueAllocFailed(int **ptr)
{
	if (ptr == NULL)
	{
		printf("Error: Insufficient Memory\n");
		return 1;
	}
	return 0;

}
/******************************************************************************
* Function name: CellAllocFailed
* Input: char *ptr (One of Queue's pointer)
* Output: 1 if alloc falid, 0 if succeced
* Operation function: Check if the pointer is NULL or not. If it's NULL - the
* allocation wasn't succssesful and return 1. Else returns 0.
* For Example:
* Note:
* *****************************************************************************/
int CellAllocFailed(int *ptr)
{
	if (ptr == NULL)
	{
		printf("Error: Insufficient Memory\n");
		return 1;
	}
	return 0;

}