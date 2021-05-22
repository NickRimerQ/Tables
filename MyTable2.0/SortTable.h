#pragma once
#include "ScanTable.h"


class SortTable : public ScanTable
{
	vector<string> arr;

	int binarySearcher(string key, int min, int max)
	{
		string person = string();
		if (min == max)
		{
			for (int i = 0; i < arr[max].length(); i++)
			{
				if (arr[max][i] == '/') break;
				person.push_back(arr[max][i]);
			}

			if (person == key)
			{
				return max;
			}
			else
			{
				return -1;
			}
		}

		if (max < min)
		{
			cout << "max < min" << endl;
			return -1;
		}

		int mid = (max - min) / 2 + min;


		for (int i = 0; i < arr[mid].length(); i++)
		{
			if (arr[mid][i] == '/') break;
			person.push_back(arr[mid][i]);
		}

		if (person < key)
		{
			return binarySearcher(key, mid + 1, max);
		}
		else if (person > key)
		{
			return binarySearcher(key, min, mid - 1);
		}
		else
		{
			return mid;
		}
	}

	void sortArr()
	{
		sort(arr.begin(), arr.end(), [](string a, string b) {return a < b; });
	}

public:
	SortTable()
	{
		Phl.Sort();

		for (int i = 0; i < Phl.getSize(); i++)
		{
			arr.push_back(Phl[i]);
		}
	}
	void insert(string str) override
	{
		arr.push_back(str);
		sortArr();
	}
	void find(string key) override
	{
		int index = binarySearcher(key, 0, arr.size() - 1);
		if (index == -1)
		{
			cout << "Такого человека нет в списке!" << endl;
			return void();
		}
		cout << arr[index] << endl;
	}
	void del(string key) override
	{
		int index = binarySearcher(key, 0, arr.size() - 1);
		if (index == -1)
		{
			cout << "Такого человека нет в списке!" << endl;
			return void();
		}
		arr.erase(arr.begin() + index);
		sortArr();
	}
};