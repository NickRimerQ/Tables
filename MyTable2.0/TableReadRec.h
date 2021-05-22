#pragma once
#include <iostream>
#include<string>
#include <fstream>
using namespace std;


string TableReading()
{
	string path = "MyFile2.txt";
	ifstream fin;
	string returner = string();
	fin.open(path);
	if (!fin.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		cout << "Файл открыт!" << endl;
		char ch;
		while (fin.get(ch))
		{
			returner.push_back(ch);
		}
	}
	fin.close();
	return returner;
}

void TableRecord(string str)
{
	string path = "NewMyFile.txt";
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		fout << str;
	}
	fout.close();
}