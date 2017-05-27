
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

int results_count = 0; // ���������� �������

// ������� showBoard() - ���������� �����.
void showBoard()
{
	out << "���������" << "\n";
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
// ������� tryQueen() - ��������� ��� �� ��� ������������� ������, �� ��������� � ����������.
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
	//��������� ���� �����
	bool rep = true; //������������� �������, ��� ��� ���������
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
	//���� ���� ���� �� ���� �������, �� ����� false
	return !rep;
}

bool check() {
	if (results_count != 0) {
		//showBoard();
		bool result = true; // ���� true, �� ����� �������� � ����������
		for (int k = 0; k < 3; k++) {
			board = turn90(SIZE, board); //��������� �� 90 ��������	
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
	//�� 1 ������� �� 2-��
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
	//�������� ���� ���������� ������
}

// ������� setQueen() - ������� ����� ���������� �������.
void setQueen(int a) // a - ����� ��������� ������ � ������� ����� ��������� ���������� �����.
{

	if (a == SIZE)
	{
		if (check())
		{
			cout << "��������� � " << ++results_count << "\n";
			showBoard();
			cout << "\n\n";
			if (results_count == 1) {
				res[0] = copy_board(board); // ����� ������� ��� �������������
			}
			else {
				//�������� ������
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
				//�������� ������ � ��������, ������ ����� ���� ������� ��������� �������
				res[results_count - 1] = copy_board(board);
			}
			return;
		}

	}
	switch (flag1) // ������ ��������� switch
	{
	case 1:
	{

			  for (int i = 0; i < SIZE; ++i)
			  {
				  // ����� ���������, ��� ���� �������� � board[a][i] ����� (�������),
				  // �� �� ����� ������������ � ���� ������, ������� � ����������.

				  if (tryQueen(a, i)) {

					  board[a][i] = 1;
					  setQueen(a + 1);
					  cout << "������������� �������:" << "\n";
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
				  // ����� ���������, ��� ���� �������� � board[a][i] ����� (�������),
				  // �� �� ����� ������������ � ���� ������, ������� � ����������.

				  if (tryQueen(a, i)) {

					  board[a][i] = 1;
					  setQueen(a + 1);
					  board[a][i] = 0;

				  }

			  }

			  return;
			  break;
	}
	default: // ���� count ����� ������ ������� ��������
		cout << "�������� ����" << endl;
	}

}

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream fin("in.txt");
	int flag;
	cout << "�������� ������ �����: " << endl;
	cout << " 1.������� " << endl;
	cout << " 2.���� " << endl;
	std::cin >> flag;

	cout << "����� �� ������������� �������: " << endl;
	cout << " 1.��" << endl;
	cout << " 2.��� " << endl;
	std::cin >> flag1;
	system("CLS");
	switch (flag) // ������ ��������� switch
	{
	case 1:
	{
			  cout << "������� ����������� �����: ";
			  std::cin >> SIZE;

			  break;
	}
	case 2:
	{
			  fin >> SIZE;

			  break;
	}
	default: // ���� count ����� ������ ������� ��������
		cout << "�������� ����" << endl;
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

	res = (int***)malloc(1 * sizeof(int**)); //���� �� ���� ������� �� ������
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
	//������� ������ ��� ��������


	setQueen(0);
	system("pause");
	return 0;

}


