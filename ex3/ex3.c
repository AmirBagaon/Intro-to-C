#include <stdio.h>

//Functions Delceration
void Or(int n, int div1, int div2);
void And(int n, int div1, int div2);
void Fibonachi(int n);
void Multiplication(int a, int b);
void Sequence(int min1, int min2);
void Deviders(int n, int div1, int div2, char key);
void DigitsSum(unsigned long number);
//End of Functions Delceration

int main()
{
	//Variables Delceration
	int num1, num2, temp, n, div1, div2, min1, min2, sum, input;
	char key;
	unsigned long number;
	//End of Variables Delceration

	//The program get number between 0-5 and respond accordingly
	printf("Please select the assignment:\n");
	scanf("%d", &input);

	//The program continue to run until it get 0 as input
	while (input != 0)
	{
		//Cases of input: 0,1,2,3,4,5 and default
		switch (input)
		{

			//In case the input is 0, the program stops
			case 0:

				return 0;
				//End of case 0

			/*****************************************************************
			* In case the input is 1, the program gets 2 numbers and print
			* the Multiplication Table for them.
			*****************************************************************/
			case 1:

				//Get 2 numbers for multiplication table
				printf("Please enter two numbers for the multiplication table:\n");
				scanf("%d %d", &num1, &num2);

				// In case num2>1 the program will swap them
				if (num1 > num2)
				{
					temp = num1;
					num1 = num2;
					num2 = temp;
				}

				//Calculate and print the Multiplication Table
				Multiplication(num1, num2);
				break;
				//End of case 1

			/*********************************************************************
			* In case the input is 2, the program gets 3 numbers: n, div1, div2
			* and a char. If the char is 'O' or 'o', the programs print the numbers
			* between 1-n that devided by div 1 or div 2. If the char is 'A' or 'a',
			* the program print the numbers between 1-n that devided by div1 and
			* div2. If the char is something else, the program print error.
			*********************************************************************/
			case 2:

				//get a number and 2 dividers
				printf("Please enter n:\n");
				scanf("%d", &n);
				printf("Please enter two dividers:\n");
				scanf("%d %d", &div1, &div2);

				//get a char as a "key"
				printf("Please enter the key:\n");
				scanf(" %c", &key);

				//Call Deviders function that respond accordingly to the key
				Deviders(n, div1, div2, key);
				break;
				//End of case 2

			/**********************************************************************
			* In case the input is 3, the program gets natural number "n", and if
			* it is positive, the function prints "n" organs of Fibonachi Sequence.
			* Otherwise, the function prints error.
			*******************************************************************/
			case 3:

				//get number n
				printf("Please enter n:\n");
				scanf("%d", &n);

				//print error if n<1 or the Fibonachi Sequence if n>=1
				if (n < 1)
					printf("INPUT ERROR\n");
				else
					Fibonachi(n);
				break;
				//End of case 3

			/********************************************************************
			* In case the input is 4, the program gets a sequence of numbers that
			* ends with -1, and print the 2 smallest positive numbers.
			********************************************************************/
			case 4:

				//set the 2 minimums to 0 so they can get positive values
				min1 = 0;
				min2 = 0;

				//call Sequence that get numbers and find the 2 smallest positives 
				Sequence(min1, min2);
				break;
				//End of case 4

			/********************************************************************
			* In case the input is 5, the program gets an unsigned long number
			* and sums it's digits
			********************************************************************/
			case 5:

				//get number
				printf("Please enter your number:\n");
				scanf("%lu", &number);
				DigitsSum(number);

				break;
				//end of case 5

			/******************************************************************
			*In case the input is not 0-5, the program print error message
			*******************************************************************/
			default:

				printf("NO SUCH ASSIGNMENT!\n");
				break;
				//End of default

		} //End of switch

		//The program get a new input and start again if it isn't 0
		printf("Please select the assignment:\n");
		scanf("%d", &input);
	} //End of while loop

	return 0;
	//End of program
}



/******************************************************************************
* Function name: Or
* Input: int n, int div1, int div2 (valid value: n>0, div1>0, div2>0)
* Output: void
* Operation function: the function print the numbers from 1-n that devided by
* div1 OR by div2.
* For Example: n=11, div1=6, div2=3 => 3 6 9.
* Note: The function will print nothing if there are no numbers that devided.
* *****************************************************************************/
void Or(int n, int div1, int div2)
{
	int i;

	//run over the numbers between 1-n
	for (i = 1; i <= n; ++i)
	{
		//print the number if it divided by div1 or div2 
		if ((i % div1 == 0) || (i % div2 == 0))
			printf("%d ", i);
	}
}

/******************************************************************************
* Function name: And
* Input: int n, int div1, int div2 (valid value: n>0, div1>0, div2>0)
* Output: void
* Operation function: the function print the numbers from 1-n that devided by
* div1 AND by div2.
* For Example: n=12, div1=6, div2=3 => 3 12.
* Note: The function will print nothing if there are no numbers that devided.
* *****************************************************************************/
void And(int n, int div1, int div2)
{
	int i;

	//run over the numbers between 1-n
	for (i = 1; i <= n; ++i)
	{
		//print the number if it divided by div1 and by div2 
		if ((i % div1 == 0) && (i % div2 == 0))
			printf("%d ", i);
	}
}

/******************************************************************************
* Function name: Fibonachi
* Input: int n (valid value n>0)
* Output: void
* Operation function: the function print "n" organs of the Fibonachi Sequence.
* n=5 => 1 1 2 3 5, n=6 => 1 1 2 3 5 8, n=8 => 1 1 2 3 5 8 13 21. etc.
* Note:
* *****************************************************************************/
void Fibonachi(int n)
{
	int previous = 0, current = 1, temp;
	//print the first organ: 1
	printf("%d ", current);
	int i;

	//print other organs. if n is 1, the loop doesn't start
	for (i = 1; i <= n - 1; i++)
	{
		//the next organ is the value of current and previous organs
		printf("%d ", (previous + current));

		//update the values of current and previous 
		temp = current;
		current += previous;
		previous = temp;
	}
	printf("\n");
}

/******************************************************************************
* Function name: Multiplication
* Input: int num1, int num2
* Output: void
* Operation function: the function print the Multiplication Table for num1*num2
* For example: num1=6, num2=8 => 36 42 48
*							     42 49 56
*								 48 56 64
* Note: num1 is bigger then num2, by the main function
* *****************************************************************************/
void Multiplication(int num1, int num2)
{
	int i, j;
	for (i = num1; i <= num2; i++)
	{
		for (j = num1; j <= num2; j++)
			//print i*j
			printf("%-4d", (i*j));

		//at the end of the line, the function goes line down
		printf("\n");
	}
}

/******************************************************************************
* Function name: Sequence
* Input: int min1, int min2 (both =0)
* Output: void
* Operation function: the function get a sequence of numbers that ends with -1,
* and print the 2 smallest numbers.
* For example: 9 1 -2 -5 8 4 -7 -1 => 1 4
* Note: The sequence can contain negative numbers. There must be at least 2
* positive numbers! Same positive number count as 1 positive!
* *****************************************************************************/
void Sequence(int min1, int min2)
{
	int num1 = 0;
	printf("Please enter your sequence:\n");
	//get numbers to num1 until the input is -1
	while (num1 != -1)
	{
		scanf(" %d", &num1);
		//check if the num is positive 
		if (num1 > 0)
			//check if min1/min2 already got positive values and if num1 is smaller
			if ((num1 < min2) || (min2 == 0))
				
				//if min1 isn't with positive value, or num1 smaller than min1
				if ((num1 < min1) || (min1 == 0))
				{
					//min1 is smaller than min2, so min2 get min1 value
					min2 = min1;
					min1 = num1;
				}
			//else if min1<=num1, but num1<min2 or min2 empty from positive value
			else
			//check that min1 dosen't already contain the number, and put it in min2
			if (min1 != num1)
				min2 = num1;
	}
	printf("%d %d\n", min1, min2);
}

/**************************************************************************
* Function name: Deviders
* Input: int n, int div1, int div2, char key
* Output: void
* Operation function: The function get number "n" and two deviders. Then it
* get a char. If the char is 'O' or 'o', the function calls to the function "Or"
* and print the numbers between 1-n that devided by div 1 or div 2.
* If the char is 'A' or 'a', the function calls the function "And"
* and print the numbers between 1-n that devided by div1 and div2.
* If the char is something else, the program print error and starts again.
* For example: 10 6 3 O => 3 6 9 10. 10 6 3 A => 6. 10 5 9 A => .
* Note: If there are no numbers that devided, the function will print nothing.
* At the end, the function goes to the next line.
* **************************************************************************/
void Deviders(int n, int div1, int div2, char key)
{
	//call Or if key is 'o' or 'O'
	if (key == 'o' || key == 'O')
		Or(n, div1, div2);
	else
		//call And if key is 'a' or 'A'
	if (key == 'a' || key == 'A')
		And(n, div1, div2);
	else
		//print error if key is none of them
		printf("ERROR IN KEY");
	printf("\n");
}

/**************************************************************************
* Function name: DigitsSum
* Input: unsigned long number
* Output: void
* Operation function: The function get a number and calculate its digits.
* For example: 12345 => 15.
* Note:
* **************************************************************************/
void DigitsSum(unsigned long number)
{
	//sum will count the number digits
	int sum = 0;

	while (number>0)
	{
		//sum get the last digit
		sum += number % 10;
		//number will be devided by 10 until it will be 0
		number = number / 10;
	}
	printf("%d\n", sum);
}