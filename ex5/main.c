
#include <stdio.h>
#include <stdlib.h>
#include "Mission1.h"
#include "Mission2.h"
#include "Mission3.h"
#include "Mission4.h"
#include "Mission5.h"
#include "Mission6.h"

int main()
{
	//Variables Delceration
	int choice;
	//End of Variables Delceration

	//Runs until coice=0, and activate function accordingly to the input
	do
	{
		printf("Please enter your input:\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			break;
		case 1:
			Mission1();
			break;
		case 2:
			Mission2();
			break;
		case 3:
			Mission3();
			break;
		case 4:
			Mission4();
			break;
		case 5:
			Mission5();
			break;
		case 6:
			Mission6();
			break;
		default:
			printf("\n");
			break;
		}
		
	} while (choice != 0);
}