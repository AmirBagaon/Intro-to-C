

#include <stdio.h>
#include <string.h>
#include "Translator.h"
#include "Calculator.h"

#define SIZE 21

int main()
{
	//Variables Delceration
	char str[SIZE];
	//End of Variables Delceration

	//runs until the input is quit
	while (1)
	{
		//Get input: Calculator, Translator or quit
		printf("Main menu, choose between the options:\n");
		printf("Matrix Calculator\n");
		printf("PigLatin Translator\n");
		fgets(str, SIZE, stdin);

		//Convert Capital letters to lower letters, and put '\0' insead of '\n'
		Capitals(str);
		WordFinisher(str);

		//if the input is quit - program is finished
		if (strcmp(str, "quit") == 0)
			return 0;
		
		//if the input is calculator - run calculator function
		if (strcmp(str, "calculator") == 0)
			Calculator();
		//if the input is translator - run translator function
		else if ((strcmp(str, "translator") == 0))
			Translator();
		//if none of them
		else
			printf("This was not an option.\n");
	}//end of while loop
}