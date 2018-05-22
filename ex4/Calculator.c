#include <stdio.h>
#include <string.h>
#include "Calculator.h"

#define ROW 15
#define COL 15

/******************************************************************************
* Function name: Calculator
* Input:
* Output: void
* Operation function: the function get size and numbers for matrix, and an
* operation char, and can do some options:
* For + : get another matrix and add it to the last matrix.
* For - : get another matrix and substract it from the last matrix.
* For * : get column and numbers for another matrix and multiplicate them.
* For t : print the transposed matrix.
* For q : quit the function (and return to main menu)
*
* For Example: for size 2*2, for the input 1 2 and for 't', will be printed: 1 3
*										   3 4								 2 4
* Note: the matrix's size must be n*m that make n>0,m>0
* *****************************************************************************/
void Calculator()
{
	//Variables Delceration
	int row, col, num, row2, col2, row3, col3;
	int i, j, check, length, flagQ, temp;
	int  matrix1[ROW][COL], matrix2[ROW][COL], matrix3[ROW][COL];
	char dummy, operation;
	//End of Variables Delceration


	printf("Welcome to the Matrix calculator\n");

	//raise a "flag" that says the operation isn't q
	flagQ = 1;
	//set the first operation to be 'c', to get a new matrix
	operation = 'c';

	//runs until q operation appeared
	while (flagQ)
	{
		//Cases of operation: +,-,*,t,c,q and default
		switch (operation)
		{

		/********************************************************************
		* In case the operation is 'c', the program get proper number for rows
		* and cols for new matrix, and get numbers to fill it.
		********************************************************************/
		case 'c':

			//Get number of rows and cols, and verify that they aren't 0
			do
			{
				printf("Please enter first matrix dimensions (row col): \n");
				scanf("%d %d", &row, &col);
			} while (!(ProperDim(row,col)));

			//Initialize matrix1 and get numbers to it
			Initialize(matrix1);
			printf("Please enter matrix elements(%dx%d): \n", row, col);
			GetMatrix(matrix1, row, col);

			break;
			//end of case 'c'
	
		/********************************************************************
		* In case the operation is '+' or '-', the program get numbers to a
		* matrix in the same size of the of the last martix, and add (if '+')
		* them or subtract (if '-') them from the last matrix. Then it print
		* the matrix.
		********************************************************************/
		case '+':
		case '-':

			//get a number and add or subtract it to matrix 1
			printf("Please enter matrix elements(%dx%d): \n", row, col);
			for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
			{
				scanf("%d", &num);

				//if the operation is +, the number will be added to matrix 1
				if (operation == '+')
					matrix1[i][j] += num;
				//otherwise it will be subtracted from matrix 1
				else matrix1[i][j] -= num;
			}

			//print matrix1
			printf("The answer is:\n");
			Print(matrix1, row, col);

			break;
			// end of case '+' or case '-'

		/********************************************************************
		* In case the operation is '*', the program get a proper column to a
		* second matrix, then get numbers to fill it, and then multiply the
		* matrixs and print the result.
		* Note: it can be done with less variables, but in order to make it
		* more convinent, i added some extra variables, with explnations.
		* col and row belong to matrix 1,
		* col2 and row2 belong to matrix 2,
		* and col3 and row3 belong to matrix 3
		********************************************************************/
		case '*':

			//in *, the cols of matrix1 has to be equal to the rows of matrix2
			row2 = col;

			//get proper number of columns for matrix2
			do
			{
				printf("Please enter column dimension of second matrix: \n");
				scanf("%d", &col2);
			} while (!(ProperDim(row2, col2)));

			//Reset matrix2 and get values into it
			Initialize(matrix2);
			printf("Please enter matrix elements(%dx%d): \n", row2, col2);
			GetMatrix(matrix2, row2, col2);

			/*

			* In matrix multiply, Matrix(row X col) * Matrix2(row2 X col2) =
			* Matrix3(rowXcol2), so Matrix3 has Matrix1 rows and Matrix2 cols.
			* Therefore we set row3=row, col3=col2. In addition, each multiply
			* is "col" organs of Matrix1 * "row2" organs of Matrix2 (col=row2)
			* so we set "length" (the number of cells should be multiply in each
			* matrix) to be ="col".
			
			*/
			row3 = row;
			col3 = col2;
			length = col;

			//Reset matrix3 and calcualte the new matrix
			Initialize(matrix3);
			for (i = 0; i < row3; i++)
			for (j = 0; j < col3; j++)
				//each "square" call MultiSum func, to calculate its value
				matrix3[i][j] += MultiSum(matrix1, matrix2, length, i, j);

			//Copy matrix 3 to matrix 1, so we can use it for next operations
			CopyMatrix(matrix3, matrix1, row3, col3);

			//Set Matrix1 rows and cols to be like those in matrix3
			row = row3;
			col = col3;

			//Print matrix1
			printf("The answer is:\n");
			Print(matrix1, row, col);

			break;
			//end of case '*' 

		/***************************************************************
		* In case the operation is 't', the program print the transposed
		* matrix of the last matrix.
		****************************************************************/
		case 't':

			//save a copy of matrix 1
			CopyMatrix(matrix1, matrix3, row, col);

			//Initialize matrix1, and set the rows to be coloumns and vice versa
			Initialize(matrix1);
			for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
				matrix1[j][i] = matrix3[i][j];

			//swap row and col, so they match to transposed matrix
			temp = row;
			row = col;
			col = temp;

			//print the transposed matrix
			printf("The answer is:\n");
			Print(matrix1, row, col);
			break;
			//end of case 't'
		
		/********************************************************************
		* In case the operation is 'q', the program will quit the loop.
		********************************************************************/
		case 'q':

			//we use dummy to catch the '\n'
			scanf("%c", &dummy);
			//turn down the "flag" that sign for the loop to continue
			flagQ = 0;

			//quit the loop in order to not get another opertaion
			continue;
			//end of case 'q'

		default:
			// in case the input for the operation wasn't (+,-,*,t ,c,q) 
			printf("This operation does not exist!\n");
			break;
			//end of default case

		}//end of switch

		
		//if operation isn't q, we get dummy for the '\n', and another operation
		scanf("%c", &dummy);
		printf("Please enter operation:(+,-,*,t,c,q)\n");
		scanf("%c", &operation);

	} //end of while loop

}

/*******************************************************************************
* Function name: Print
* Input: int matrix1[ROW][COL], int row, int col (valid value: row>0, col>0)
* Output: void
* Operation function: the function print the numbers in the matrix
* Note: The function print only "row" (that was in input) rows and "col" cols of
* the matrix. The others not relevant here.
* *****************************************************************************/
void Print(int matrix1[ROW][COL], int row, int col)
{
	int i, j;
	for (i = 0; i <row; i++)
	{
		for (j = 0; j <col; j++)
			printf("%4d ", matrix1[i][j]);
		printf("\n");
	}
}

/******************************************************************************
* Function name: MultiSum
* Input: int matrix1[ROW][COL], int matrix2[ROW][COL], int length,
* int place1, int place2
* Output: sum
* Operation function: the function get 2 matrixs and calculate the sum of
* matrix1's row * matrix's 2 col. Then, it return the sum
* For Example: 1 2 3  *  4
*						 5			-> sum= 1*4+2*5+3*6=32
*						 6     
* Note: Length is row/col length. place1 is matrix1's precise row, place2 is 
* matrix2's precise col, so the function know which row*col it may calculate.
* *****************************************************************************/
int MultiSum(int matrix1[ROW][COL], int matrix2[ROW][COL], int length, int place1, int place2)
{
	int i;
	int sum = 0;
	for (i = 0; i < length; i++)
		sum += matrix1[place1][i] * matrix2[i][place2];

	return sum;
}
/******************************************************************************
* Function name: Initialize
* Input: int matrix[ROW][COL]
* Output: void
* Operation function: the function get matrix and "reset" it: fill it with 0
* in all the cells.
* Note:
* *****************************************************************************/
void Initialize(int matrix[ROW][COL])
{
	int i, j;
	for (i = 0; i < ROW; i++)
	for (j = 0; j < COL; j++)
		matrix[i][j] = 0;
}

/******************************************************************************
* Function name: GetMatrix
* Input: int matrix[ROW][COL], int row, int col
* Output: void
* Operation function: the function fill matrix with numbers it get from user
* Note: The function fill only "row" (that was in input) rows and "col" cols of
* the matrix. The others not relevant here.
* *****************************************************************************/
void GetMatrix(int matrix[ROW][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	for (j = 0; j < col; j++)
		scanf("%d", &matrix[i][j]);
}

/******************************************************************************
* Function name: CopyMatrix
* Input: int matrix[ROW][COL], int matrix2[ROW][COL], int row, int col
* Output: void
* Operation function: the function copy matrix values to another matrix
* Note: The function copy only "row" (that was in input) rows and "col" cols of
* the matrix. The others not relevant here.
* *****************************************************************************/
void CopyMatrix(int matrix[ROW][COL], int matrix2[ROW][COL], int row, int col)
{
	Initialize(matrix2);
	int i, j;
	for (i = 0; i < row; i++)
	for (j = 0; j < col; j++)
		matrix2[i][j] = matrix[i][j];
}

/******************************************************************************
* Function name: ProperDim
* Input: int row, int col
* Output: 0 or 1
* Operation function: the function return 1 if the input for the rows and cols
* of a matrix is bigger than 0. If not, it print error and return 0.
* Note: 
* *****************************************************************************/
int ProperDim(int row, int col)
{
	//print error if rows or cols <= 0
	if ((row <= 0) || (col <= 0))
	{
		printf("Error\n");
		return 0;
	}
	else return 1;
	
}