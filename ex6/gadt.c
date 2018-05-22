
#include <stdio.h>
#include <stdlib.h>
#include "gadt.h"

//Build struct of node
typedef struct Node{
	//Value and Next
	ELM val;
	struct Node *next;

	//The functions
	void(*cpy_elm) (ELM, ELM);
	int(*cmp_elm)(ELM, ELM);
	void(*free_elm) (ELM);
	ELM(*create_elm)();
	void(*print_elm)(ELM);
	ELM(*add_elm_to_elm)(ELM, ELM);
} Node;

/******************************************************************************
* Function name: SLCreate
* Input:pointer to a value (point or string), and pointer to functions:
* create_elm,cpy_elm, cmp_elm, free_elm, print_elm, add_elm_to_elm.
* Output: a pointer to struct (of type HEAD) that contains value, functions, and
* pointer to next node.
* Operation function: The function allocates memory for the node and it value, 
* and than insert the functions that it got, to the struct options. 
* Then set 'next' as NULL.
* For Example:
* Note:
* *****************************************************************************/
HEAD SLCreate(ELM head_val, ELM(*create_elm)(), void(*cpy_elm)(ELM, ELM), int(*cmp_elm)(ELM, ELM), void(*free_elm)(ELM),
	void(*print_elm)(ELM), ELM(*add_elm_to_elm)(ELM, ELM))
{
	//Allocates memory for the the organ (node) and for it's value
	Node *organ = (Node*)malloc(sizeof(struct Node));
	if (organ == NULL)
		return NULL;
	organ->val = (ELM)create_elm();
	if (organ->val == NULL)
		return NULL;

	//Copy the functions
	organ->create_elm = create_elm;
	organ->cpy_elm = cpy_elm;
	organ->cmp_elm = cmp_elm;
	organ->free_elm = free_elm;
	organ->print_elm = print_elm;
	organ->add_elm_to_elm = add_elm_to_elm;

	//Set Value and next
	cpy_elm(organ->val, head_val);
	organ->next = NULL;
	return organ;
}

/******************************************************************************
* Function name: SLDestroy
* Input: The head of the linked list (type HEAD)
* Output: void
* Operation function: The function destroy the list, in other words, free every
* value and node in the list.
* For Example:
* Note:
* *****************************************************************************/

void SLDestroy(HEAD head)
{
	Node* n = (Node*)(head);
	Node* after;
	while (n != NULL)
	{
		//Keep the next so we won't lose it in freeing n
		after = n->next;
		//free the value and n
		n->free_elm(n->val);
		free(n);

		n = after;
	}
}
/******************************************************************************
* Function name: SLAddListElement
* Input: Pointer to a the head of the list, and ELM (point or String)
* Output: RESULT - 'success' if the node has been added, 'outOfMem' if the
* allocation failed.
* Operation function: The function allocates memory for the node and it value,
* and than insert the functions that it got, to the struct options.
* Then set 'next' as NULL.
* For Example:
* Note:
* *****************************************************************************/

RESULT SLAddListElement(HEAD* head, ELM node)
{
	Node* n = (Node*)(*head);
	Node* n2 = (Node*)(*head);
	Node* temp = (Node*)(*head);
	int check = 1;

	//Allocates memory for another node and for its value
	n2 = (Node*)malloc(sizeof(Node));
	if (n2 == NULL)
		return outOfMem;
	n2->val = temp->create_elm();
	if (n2->val == NULL)
	{
		free(n2);
		return outOfMem;
	}
	
	//As long we didn't reach the end of the list, and didn't find the element
	while ((n != NULL) && (check))
	{
		//When node<=n's val, we insert it before n
		if ((n->cmp_elm(n->val, node) >= 0))
		{
			n->cpy_elm(n2->val, n->val);
			n->cpy_elm(n->val, node);
			//Set next of both
			n2->next = n->next;
			n->next = n2;
			check = 0;
		}
		//When node is bigger than all the other values
		if (((n->next) == NULL) && (check))
		{
			temp->cpy_elm(n2->val, node);
			n2->next = NULL;
			n->next = n2;
			check = 0;
		}
		else
			n = n->next;
	}

	//Copy the functions
	n2->add_elm_to_elm = temp->add_elm_to_elm;
	n2->cpy_elm = temp->cpy_elm;
	n2->create_elm = temp->create_elm;
	n2->free_elm = temp->free_elm;
	n2->print_elm = temp->print_elm;
	n2->cmp_elm = temp->cmp_elm;
	return success;
}

/******************************************************************************
* Function name: SLRemoveElement
* Input: Pointer to a the head of the list, and ELM (point or String)
* Output: RESULT - 'success' if the node has been removed, 'outOfMem' if the
* allocation failed, 'failure' if there was only one node and we removed it,
* in that case the program should end, 'badArgs' if the value isn't in list.
* Operation function:  Checks if the item in the list. Then, goes through the 
* list. If theres is only one node, it removes it. Otherwise, it goes until it
* find the node with this value. Then it set the previous-node's next as 
* the after-node (or NULL if it is the last node), and free the node. 
* For Example:
* Note: The function prints FALSE if the element isn't in the list
* *****************************************************************************/
RESULT SLRemoveElement(HEAD* head, ELM node)
{
	int check = 1, count=0;
	//Check if the value is in the list
	if ((SLFindElement(*head, node) == NULL))
	{
		printf("FALSE\n");
		return badArgs;
	}
	Node* n1 = (Node*)(*head);
	Node* n2 = (Node*)(*head);
	Node *temp = (Node*)(*head);;

	while (check)
	{
		count++;
		//If we reach the last organ in the list
		if (n1->next == NULL)
		{
			//Free the value and the node
			n1->free_elm(n1->val);
			free(n1);

			//If it was the only node, the program should stop, so return failure
			if (count==1)
				return failure;
			else
			{
				//set the previous-node's next to be NULL
				n2->next = NULL;
				return success;
			}
		}

		//If we found the value in the middle of the list
		if ((n1->cmp_elm(n1->val, node) == 0))
		{
			//set n1's next as the node after n2, copy n2's value and delete n2
			n2 = n1->next;
			n1->cpy_elm(n1->val, n2->val);
			n1->next = n2->next;
			//Free n2 and its value
			n2->free_elm(n2->val);
			free(n2);
			check = 0;
		}
		else
		{	
			//go forward in the list
			n2 = n1;
			n1 = n1->next;
		}
	}
	return success;
}

/******************************************************************************
* Function name: SLFindElement
* Input: The head of the list, and ELM (point or String)
* Output: Returns a pointer to the node that contains the value of the ELM the
* functions got, or NULL if it isn't in the list.
* Operation function:  Checks if the item in the list. Then, goes through the
* list. If theres is only one node, it removes it. Otherwise, it goes until it
* find the node with this value. Then it set the previous-node's next as
* the after-node (or NULL if it is the last node), and free the node.
* For Example:
* Note:
* *****************************************************************************/
ELM SLFindElement(HEAD head, ELM node)
{
	Node* n1 = (Node*)head;
	while ((n1 != NULL))
	{
		//if the value of the nodes is equal
		if (n1->cmp_elm(n1->val, node) == 0)
			return n1;
		n1 = n1->next;
	}
	return NULL;
}

/******************************************************************************
* Function name: SLAddElmToElm
* Input: pointer to the head of the list, ELM (point or String) to add to,
* and ELM to add from.
* Output: void
* Operation function: Adds a value to a node in the list, if it is in the list.
* The functions find the node, add the value to it, remove it and insert it
* it again, so now the list continue to be sorted.
* For Example: ab, c -> abc. (2,4),(8,9)->(10,13)
* Note:
* *****************************************************************************/

void SLAddElmToElm(HEAD* head, ELM toEl, ELM addEl)
{
	Node* temp = (Node*)(*head);
	Node* n = (Node*)(*head);
	int check = 1, count = 0;

	//As long the item hasn't been found
	while ((n != NULL) && (check))
	{
		count++;
		//When the node is equal to node in the list
		if ((n->cmp_elm(n->val, toEl) == 0))
			check = 0;
		else
			n = n->next;
	}
	//If the item isn't in the list
	if (n == NULL)
		return;

	//If there is only one node - just change its value
	if (count == 1)
		if (n->next == NULL)
		{
			n->val = n->add_elm_to_elm(n->val, addEl);
			return;
		}
	
	//Else, we want the list to be sorted, so we remove and insert it again
	SLRemoveElement(head, toEl);
	temp->add_elm_to_elm(toEl, addEl);
	SLAddListElement(head, toEl);
}

/******************************************************************************
* Function name: SLPrintElements
* Input: pointer to the head of the list
* Output: void
* Operation function: Print the values of the nodes in the list
* For Example: 
* Note:
* *****************************************************************************/

void SLPrintElements(HEAD* head)
{
	Node* n1 = (Node*)head;
	int i,count = 0;
	
	while (n1 != NULL)
	{
		//print tab (int the next line) for each organ
		for (i = 0; i<count; i++)
			printf("\t");
		
		//print each organ
		n1->print_elm(n1->val);
		n1 = n1->next;
		count++;
	}
}
/******************************************************************************
* Function name: SLSize
* Input: pointer to the head of the list
* Output: returns the list's size
* Operation function: Calculate and return the number of the nodes in the list
* For Example: (2,3),(10,20) -> 2
* Note:
* *****************************************************************************/
int SLSize(HEAD* head)
{
	int count = 0;
	Node* n1 = (Node*)head;
	while (n1 != NULL)
	{
		n1 = n1->next;
		count++;
	}
	return count;
}

