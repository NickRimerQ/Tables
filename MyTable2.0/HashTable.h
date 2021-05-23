#pragma once
#include "ScanTable.h"


int HashFunc(string key)
{
	int value = toupper(key[0]) - '�' - 256 + (toupper(key[1]) - '�' - 256) * 32;
	return value;
}

vector<list<string>> table(1024);

class HashTable : public Table
{
public:
	HashTable()
	{
		string str = TableReading();

		string fullName = string();
		string person = string();

		for (int i = 0; i < str.length() + 1; i++)
		{
			if (str[i] == '\n' || i == str.length())
			{
				table[HashFunc(fullName)].push_front(person);
				fullName = string();
				person = string();
				continue;
			}
			person.push_back(str[i]);

			if (fullName.length() != 2 && str[i] >= '�' && str[i] <= '�')
			{
				fullName.push_back(str[i]);
			}
		}
	}

	virtual void insert(string key) override
	{
		string fullName = string();
		for (int i = 0; i < key.length(); i++)
		{
			if (fullName.length() != 2 && key[i] >= '�' && key[i] <= '�')
			{
				fullName.push_back(key[i]);
			}
		}

		int index = HashFunc(fullName);
		table[index].push_back(key);
		return void();
	}

	virtual void find(string key) override
	{
		string fullName = string();
		for (int i = 0; i < key.length(); i++)
		{
			if (fullName.length() != 2 && key[i] >= '�' && key[i] <= '�')
			{
				fullName.push_back(key[i]);
			}
		}

		int index = HashFunc(fullName);
		if (table[index].size() == 0)
		{
			cout << "������ �������� ��� � ������!" << endl;
			return void();
		}


		for (auto iter = table[index].begin(); iter != table[index].end(); iter++)
		{
			if ((*iter).find(key) != string::npos)
			{
				cout << *iter << endl;
				return void();
			}
		}
		cout << "������ �������� ��� � ������!" << endl;
		return void();
	}

	virtual void del(string key) override
	{
		string fullName = string();
		for (int i = 0; i < key.length(); i++)
		{
			if (fullName.length() != 2 && key[i] >= '�' && key[i] <= '�')
			{
				fullName.push_back(key[i]);
			}
		}

		int index = HashFunc(fullName);
		if (table[index].size() == 0)
		{
			cout << "������ �������� ��� � ������!" << endl;
			return void();
		}


		for (auto iter = table[index].begin(); iter != table[index].end(); iter++)
		{
			if ((*iter).find(key) != string::npos)
			{
				//cout << *iter << endl;
				table[index].erase(iter);
				return void();
			}
		}
		cout << "������ �������� ��� � ������!" << endl;
		return void();
	}

};