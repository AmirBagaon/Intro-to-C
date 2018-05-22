
//File: Calculator.h
#ifndef Calculator_H
#define Calculator_H
#define COL 15
#define ROW 15


void Print(int matrix[ROW][COL], int row, int col);
void Initialize(int matrix[ROW][COL]);
void GetMatrix(int matrix[ROW][COL], int row, int col);
int MultiSum(int matrix[ROW][COL], int matrix2[ROW][COL], int length, int place1, int place2);
void CopyMatrix(int copyFrom[ROW][COL], int copyTo[ROW][COL], int row, int col);
void Calculator();

#endif