#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount,
	const int Low, const int High, int i, int j);
void Print(int** a, const int rowCount, const int colCount);
void Sort(int** a, const int rowCount, const int colCount, int i, int j);
void Change(int** a, const int row1, const int row2, const int colCount);
void Sum_Count_Replace(int** Z, const int rowCount, const int colCount, int& S, int& k);int main() {	srand((unsigned)time(NULL));
	int Low = 4;
	int High = 45;
	int rowCount = 9;
	int colCount = 7;	int** Z = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		Z[i] = new int[colCount];
	cout << "Start Matrix: " << endl;
	Create(Z, rowCount, colCount, Low, High, 0, 0);
	Print(Z, rowCount, colCount);
	cout << "Sorted Matrix: " << endl;
	Sort(Z, rowCount, colCount, 0, 0);
	Print(Z, rowCount, colCount);
	int S = 0;
	int k = 0;
	Sum_Count_Replace(Z, rowCount, colCount, S, k);
	cout << "S = " << S << endl;
	cout << "k = " << k << endl;
	cout << " " << endl;
	cout << "Modified Matrix: " << endl;
	Print(Z, rowCount, colCount);
	for (int i = 0; i < rowCount; i++)
		delete[] Z[i];
	delete[] Z;
	return 0;}void Create(int** a, const int rowCount, const int colCount,
	const int Low, const int High, int i, int j)
{
	a[i][j] = Low + rand() % (High - Low + 1);
	if (j < colCount - 1)
		Create(a, rowCount, colCount, Low, High, i, j + 1);
	else
		if (i < rowCount - 1)
			Create(a, rowCount, colCount, Low, High, i + 1, 0);
}
void RecursivePrint(int** Z, const int rowCount, const int colCount, int row, int col)
{
	if (row >= rowCount)
		return;

	if (col < colCount)
	{
		cout << setw(4) << Z[row][col];
		RecursivePrint(Z, rowCount, colCount, row, col + 1);
	}
	else
	{
		cout << endl;
		RecursivePrint(Z, rowCount, colCount, row + 1, 0);
	}
}

void Print(int** Z, const int rowCount, const int colCount)
{
	RecursivePrint(Z, rowCount, colCount, 0, 0);
	cout << endl;
}void RecursiveChange(int** Z, const int col1, const int col2, const int colCount, int row = 0) {
	if (row >= colCount)
		return;


	int tmp = Z[row][col1];
	Z[row][col1] = Z[row][col2];
	Z[row][col2] = tmp;


	RecursiveChange(Z, col1, col2, colCount, row + 1);
}

void Change(int** Z, const int col1, const int col2, const int colCount) {
	RecursiveChange(Z, col1, col2, colCount);
}void Sort(int** Z, int rowCount, int colCount, int i, int j) {
	if (i < rowCount) {
		if (j < colCount - 1) {
			bool shouldSwap = false;

			if (Z[0][j] < Z[0][j + 1]) {
				shouldSwap = true;
			}
			else if (Z[0][j] == Z[0][j + 1] && Z[1][j] > Z[1][j + 1]) {
				shouldSwap = true;
			}
			else if (Z[0][j] == Z[0][j + 1] && Z[1][j] == Z[1][j + 1] && Z[2][j] < Z[2][j + 1]) {
				shouldSwap = true;
			}

			if (shouldSwap) {
				Change(Z, j, j + 1, rowCount);
			}

			Sort(Z, rowCount, colCount, i, j + 1);
		}
		else {
			Sort(Z, rowCount, colCount, i + 1, 0);
		}
	}
}
void Recursive_Sum_Count_Replace(int** Z, const int rowCount, const int colCount, int& S, int& k, int i, int j) {
	if (i >= rowCount) {
		return;
	}

	if (j < colCount) {
		if (Z[i][j] % 2 == 0 && !(i % 2 != 0 || j % 2 != 0)) {
			S += Z[i][j];
			k++;
			Z[i][j] = 0;
		}
		Recursive_Sum_Count_Replace(Z, rowCount, colCount, S, k, i, j + 1);
	}
	else {
		Recursive_Sum_Count_Replace(Z, rowCount, colCount, S, k, i + 1, 0);
	}
}

void Sum_Count_Replace(int** Z, const int rowCount, const int colCount, int& S, int& k) {
	S = 0;
	k = 0;
	Recursive_Sum_Count_Replace(Z, rowCount, colCount, S, k, 0, 0);
}