#include <stdio.h>
#include <math.h>
int main()
{
	//Variables Delceration
	int input, score, num1, num2, num3, max, min;
	char rank, dummy, char1, char2, char3, name1, name2;
	float avg, test1, exercise1, test2, exercise2;
	double grade1, grade2;
	//End of Variables Delceration

	//The program get number between 0-4 and respond accordingly
	printf("Please enter your input:\n");
	scanf("%d", &input);

	switch (input)
	{
		//In case the input is 0, the program stops
		case 0:

			return 0;
		//End of case 0

		/*****************************************************************
		* In case the input is 1, the program gets a score, checks if it *
		* is a real score, and prints the appropriate rank.              *
		*****************************************************************/
		case 1:

			printf("Please enter your score:\n");
			scanf("%d", &score);

			//Check if the input is a real score (between 0-100) and stop if not
			if (score > 100 || score < 0)
			{
				printf("Error");
				break;
			}

			//Calculate the appropriate rank for the score
			else if (score >= 90)
				rank = 'A';
			else if (score >= 80 && score <= 89)
				rank = 'B';
			else if (score >= 70 && score <= 79)
				rank = 'C';
			else if (score >= 60 && score <= 69)
				rank = 'D';
			else
				rank = 'E';

			//Print the score and it's rank
			printf("The rank for %d is: %c\n", score, rank);
			break;
			//End of case 1

		/*******************************************************************
		* In case the input is 2, the program gets 3 numbers,and calculate *
		* their minimum, maximum and the average                           *
		*******************************************************************/
		case 2:

			//Get 3 numbers
			printf("Please enter three numbers:\n");
			scanf("%d %d %d", &num1, &num2, &num3);

			//Caculate the minimum and the maximum
			if (num1 > num2)
			{
				if (num1 > num3)
				{
					max = num1;
					if (num3 > num2)
						min = num2;
					else min = num3;
				}
				else 
				//If num1 > num2 and num3 >= num1
				{
					max = num3;
					min = num2;
				}
			}
			else
			//If num1 <= num2
			if (num1 <= num3)
			{
				min = num1;
				if (num2 >= num3)
					max = num2;
				else
					max = num3;

			}
			else 
			// if num2 >= num1 and also num1>num 3
			{
				min = num3;
				max = num2;
			}

			// Print minimum and maximum
			printf("The minimal value is: %d\n", min);
			printf("The maximal value is: %d\n", max);
			//Calculate and print the average
			avg = ((float)(num1 + num2 + num3) / 3);
			printf("The average is: %.2f\n", avg);

			break;
			//End of case 2

		/******************************************************************
		* In case the input is 3, the program gets 3 chars (F.E First,	  *
		* Second, Third) and print them in a special order:				  *
		* First     													  *
		* First															  *
		* Second														  *
		* Third															  *
		* Second@First@Third											  *
		* Third															  *
		* Third#First#Second											  *
		*******************************************************************/
		case 3:

			scanf("%c", &dummy); // dummy recevies the ‘\n’ char we got after presssing 3
			printf("Please enter three chars:\n");
			scanf("%c %c %c", &char1, &char2, &char3);
			//Print the letters in the special order
			printf("%c\n", char1);
			printf("%c\n%c\n%c\n", char1, char2, char3);
			printf("%c@%c@%c\n", char1, char2, char3);
			printf("%c\n", char3);
			printf("%c#%c#%c\n", char3, char2, char1);

			break;
			//End of case 3

		/********************************************************************
		* In case the input is 4, the program gets a test grade, an exercise*
		* grade and the first letter of the name, for 2 students.			*
		* The program checks if the grades are real (between 0-100) and then*
		* calculates their final grade, which based on: 8*sqrt of the test's*
		* grade, + 0.1 * the exercise's grade.								*
		********************************************************************/
		case 4:

			//Gets input of test, exercise, and first letter of student 1
			printf("Please enter two course details:\n");
			scanf("%f %f %c", &test1, &exercise1, &name1);

			//Check if the grades are between 0-100
			if ((test1<0) || (exercise1<0) || (test1>100) || (exercise1>100))
			{
				printf("Error");
				break;
			}
			
			//Gets input of test, exercise, and first letter of student 2
			scanf("%f %f %c", &test2, &exercise2, &name2);
			
			//Check if the grades are between 0-100
			if ((test2<0) || (exercise2<0) || (test2>100) || (exercise2>100))
			{
				printf("Error");
				break;
			}

			//Calculating final grade
			grade1 = ((8 * sqrt(test1)) + 0.1*exercise1);
			grade2 = ((8 * sqrt(test2)) + 0.1*exercise2);

			//Print final grades
			printf("The final grade of %c is: %.2f\n", name1, grade1);
			printf("The final grade of %c is: %.2f\n", name2, grade2);

			break;
			//End of case 4

		//In case the input isn't between 0-4
		default:
			printf("Wrong key\n");
		
		//End of the program
		return 0;
	}

}