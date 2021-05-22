#pragma once
#include "Node_and_Table.h"


class ScanTable : public Table
{
public:
	ScanTable()
	{
		Phl.Push_Back(TableReading());

	}
	void insert(string str) override
	{
		Phl.Push_Back(str);
		cout << endl;

	}
	void find(string key) override
	{
		Phl.Finding(key);
		cout << endl;
	}
	void del(string key) override
	{
		Phl.Removing(key);
	}
	void Print()
	{
		Phl.Print();
	}
};