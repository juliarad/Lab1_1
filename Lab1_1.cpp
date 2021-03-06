﻿/*Радкевич Ю.С. 91 группа 

Задача связности.
Предположим, что имеется последовательность пар целых чисел (пара p-q интерпретируется в значении "р связано с q"). 
Если р связано с q, a q связано с r, то р связано с r. 
Задача состоит в написании программы для исключения лишних пар из набора:
когда программа получает очередную пару р-q, она должна добавлять эту пару только в том случае, если из предыдущих пар не следует, что что р связано с q.

При решении задачи использовался алгоритм быстрого поиска. 
В элементах массива, соответствующих связанным между собой числам, хранятся одинаковые значения*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static const int N = 2001; //в элементах с номерами 0-1000 будут храниться числа от 0 до 1000, а в элементах 1001-2000 отрицательные от -1 до -1000 


int Menu() {
	cout << "1 - ввести последовательность с консоли\n2 - открыть готовый файл" << endl;
	int a;
	do {
		cin >> a;
	} while (a != 1 && a != 2);
	return a;
}

string ReadConsole(){
	string fname;
	cout << "Введите имя файла, куда будет записана последовательность ";
	cin >> fname;
	ofstream fcreate(fname);

	cout << "Введите последовательность чисел.\nПризнаком конца является ввод числа" << N / 2 + 1<<endl;
	int a;
	cin >> a;
	while (a != N / 2 + 1 ) {
		fcreate << a<<" ";
		cin >> a;
	}
	fcreate.close();
	return fname;
}

int main()
{
	setlocale(LC_ALL, "rus");

	ofstream fout("Result.txt");
	ifstream fin;
	string fname;
	ofstream fcreate;
	int i = Menu();
	switch (i) {
	case 1:
	{
		fname = ReadConsole();
		fin.open(fname);
		break;
	}
	case 2:
		do {
			cout << "Введите имя файла: ";
			cin >> fname;
			fin.open(fname);
		} while (!fin.is_open()); //проверка выбранного файла на существование
	}

	int first, second, id[N];

	for (i = 0; i < N; i++)
		id[i] = i;
	
	while (fin >> first >> second) {//считывание пар чисел

		//проверка велличины числа
		if (abs(first) > N / 2 || abs(second) > N / 2)
			continue;
		//изменение значения считанного числа, в случае, если оно  меньше 0 с целью дальнейшего использования в качестве индекса
		if (first < 0)
			first = -first + N / 2;
		if (second < 0)
			second = -second + N / 2;

		int temp = id[first];

		//если числа уже связаны друг с другом, то не добавляем новую пару, а сразу переходим на следующую итерацию
		if (temp==id[second])
			continue; 

		//проходим по всему массиву, находим все числа, связанные с первым и связываем их со вторым
		for (i=0; i<N; i++)
			if (id[i] == temp)
				id[i]=id[second];

		//Для отрицательных чисел возврат к исходным значениям для правильной записи в файл
		if (first > N / 2)
			first = N / 2 - first;
		if (second > N / 2)
			second = N / 2 - second;		

		//добавляем к результату новую пару связанных чисел
		fout << " " << first << " " << second << endl;
	}
	cout << "Результат записан в файл Result.txt";

	fin.close();
	fout.close();

	return 0;
}

