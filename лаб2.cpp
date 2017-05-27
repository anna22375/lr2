
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

int SIZE;
int **board;
int ***res;
int flag1;
ofstream out("out.txt");

int results_count = 0; // Количество решений

// Функция showBoard() - отображает доску.
void showBoard()
{
	out << "Результат" << "\n";
	for (int a = 0; a < SIZE; ++a)
	{
		for (int b = 0; b < SIZE; ++b)
		{
			cout << ((board[a][b]) ? "Q " : ". ");

			out << ((board[a][b]) ? "Q " : ". ");

		}
		cout << '\n';
		out << '\n';
	}
	out << "\n\n";
}

int **turn90(int n, int **a) {
	int i, j;
	int **b;
	b = new int *[n];
	for (i = 0; i < n; i++)
		b[i] = new int[n];
	for (i = 0; i < n; i++)
	for (j = 0; j < n; j++) {
		b[j][n - i - 1] = a[i][j];

	}
	return b;
}
// Функция tryQueen() - проверяет нет ли уже установленных ферзей, по вертикали и диагоналям.
bool tryQueen(int a, int b)
{
	for (int i = 0; i < a; ++i)
	{
		if (board[i][b])
		{
			return false;
		}
	}

	for (int i = 1; i <= a && b - i >= 0; ++i)
	{
		if (board[a - i][b - i])
		{
			return false;
		}
	}

	for (int i = 1; i <= a && b + i < SIZE; i++)
	{
		if (board[a - i][b + i])
		{
			return false;
		}
	}
	return true;
}

bool check2(int **board1, int **board2) {
	//сравнение двух досок
	bool rep = true; //первоначально считаем, что они одинаковы
	for (int i = 0; i<SIZE; i++) {
		for (int j = 0; j<SIZE; j++) {
			if (board1[i][j] == board2[i][j]) {
				rep *= true;
			}
			else {
				rep *= false;
			}
		}
	}
	//если есть хотя бы одно отличие, то будет false
	return !rep;
}

bool check() {
	if (results_count != 0) {
		//showBoard();
		bool result = true; // если true, то можем записать в результаты
		for (int k = 0; k < 3; k++) {
			board = turn90(SIZE, board); //повернули на 90 градусов	
			//showBoard();
			for (int j = 0; j < results_count; j++) {
				result *= check2(board, res[j]);
			}
		}
		board = turn90(SIZE, board);
		return result;
	}
	else {
		return true;
	}
}

int** copy_board(int**board1) {
	//из 1 копирую во 2-ую
	int **temp = (int**)malloc(SIZE * sizeof(int*));
	for (int i = 0; i<SIZE; i++) {
		temp[i] = (int*)malloc(SIZE * sizeof(int));
	}
	for (int i = 0; i<SIZE; i++) {
		for (int j = 0; j<SIZE; j++) {
			temp[i][j] = board1[i][j];
		}
	}
	return temp;
	//возможно надо освободить память
}

// Функция setQueen() - пробует найти результаты решений.
void setQueen(int a) // a - номер очередной строки в которую нужно поставить очередного ферзя.
{

	if (a == SIZE)
	{
		if (check())
		{
			cout << "Результат № " << ++results_count << "\n";
			showBoard();
			cout << "\n\n";
			if (results_count == 1) {
				res[0] = copy_board(board); // нужна функция для переписывания
			}
			else {
				//выделяем память
				res = (int***)realloc(res, results_count * sizeof(int**));
				res[results_count - 1] = (int**)malloc(SIZE * sizeof(int*));
				for (int i = 0; i < SIZE; ++i)
				{
					res[results_count - 1][i] = (int*)malloc(SIZE * sizeof(int));
					for (int j = 0; j < SIZE; ++j)
					{
						res[results_count - 1][i][j] = 0;
					}
				}
				//выделили память и обнулили, теперь нужно туда занести найденное решение
				res[results_count - 1] = copy_board(board);
			}
			return;
		}

	}
	switch (flag1) // начало оператора switch
	{
	case 1:
	{

			  for (int i = 0; i < SIZE; ++i)
			  {
				  // Здесь проверяем, что если поставим в board[a][i] ферзя (единицу),
				  // то он будет единственным в этой строке, столбце и диагоналях.

				  if (tryQueen(a, i)) {

					  board[a][i] = 1;
					  setQueen(a + 1);
					  cout << "Промежуточные решения:" << "\n";
					  showBoard();
					  cout << "\n\n";
					  board[a][i] = 0;
				  }

			  }

			  return;
			  break;
	}
	case 2:
	{
			  for (int i = 0; i < SIZE; ++i)
			  {
				  // Здесь проверяем, что если поставим в board[a][i] ферзя (единицу),
				  // то он будет единственным в этой строке, столбце и диагоналях.

				  if (tryQueen(a, i)) {

					  board[a][i] = 1;
					  setQueen(a + 1);
					  board[a][i] = 0;

				  }

			  }

			  return;
			  break;
	}
	default: // если count равно любому другому значению
		cout << "Неверный ввод" << endl;
	}

}

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream fin("in.txt");
	int flag;
	cout << "Выберите способ ввода: " << endl;
	cout << " 1.Консоль " << endl;
	cout << " 2.Файл " << endl;
	std::cin >> flag;

	cout << "Нужны ли промежуточные решения: " << endl;
	cout << " 1.Да" << endl;
	cout << " 2.Нет " << endl;
	std::cin >> flag1;
	system("CLS");
	switch (flag) // начало оператора switch
	{
	case 1:
	{
			  cout << "Введите размерность доски: ";
			  std::cin >> SIZE;

			  break;
	}
	case 2:
	{
			  fin >> SIZE;

			  break;
	}
	default: // если count равно любому другому значению
		cout << "Неверный ввод" << endl;
	}


	board = new int*[SIZE];
	for (int i = 0; i < SIZE; ++i)
	{
		board[i] = new int[SIZE];
	}
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			board[i][j] = 0;
		}
	}

	res = (int***)malloc(1 * sizeof(int**)); //хотя бы один вариант мы найдем
	res[0] = (int**)malloc(SIZE * sizeof(int*));
	for (int j = 0; j<SIZE; j++) {
		res[0][j] = (int*)malloc(SIZE * sizeof(int));
	}
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			res[0][i][j] = 0;
		}
	}
	//создали массив для хранения


	setQueen(0);
	system("pause");
	return 0;

}


