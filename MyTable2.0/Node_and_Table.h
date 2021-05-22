#pragma once
#include "TableReadRec.h"
#include <vector>
#include <list>
#include <algorithm>


class Table;

class Psevdo_HList
{
	friend Table;


private:
	class Node
	{
	public:
		Node* pNext;
		Node* pDown;
		string data;

		Node(string data_ = string(), Node* pNext_ = nullptr, Node* pDown_ = nullptr)
		{
			data = data_;
			pNext = pNext_;
			pDown = pDown_;
		}
	};

	Node* head;

	int NodeCounter;

public:
	Psevdo_HList()
	{
		head = nullptr;
		NodeCounter = 0;
	}

	~Psevdo_HList()
	{
		if (head != nullptr)
		{
			string STR = string();
			Node* saverNext = head;
			Node* saverDown = head;
			while (saverNext->pNext != nullptr)
			{
				saverDown = saverNext;
				while (saverDown->pDown != nullptr)
				{
					STR += saverDown->data;
					STR += '/';
					saverDown = saverDown->pDown;
				}
				STR += saverDown->data;
				STR += '\n';
				saverNext = saverNext->pNext;
			}
			saverDown = saverNext;
			while (saverDown->pDown != nullptr)
			{
				STR += saverDown->data;
				STR += '/';
				saverDown = saverDown->pDown;
			}
			STR += saverDown->data;
			TableRecord(STR);


			if (head != nullptr)
			{
				while (1)
				{
					if (head->pDown == nullptr && head->pNext == nullptr)
					{
						break;
					}
					Node* current = head;
					Node* prev = head;

					while (current->pNext != nullptr)
					{
						current = current->pNext;
						if (current->pNext != nullptr)
						{
							prev = prev->pNext;
						}
					}
					while (current->pDown != nullptr)
					{
						if (prev == head && current == head)
						{
							current = current->pDown;
							if (current->pDown != nullptr)
							{
								current = current->pDown;
							}
							//if(prev->pNext == nullptr && current->pDown != nullptr) //добавил условие справа
							//{
							//	prev = prev->pDown;
							//}
							if (prev->pNext == nullptr)// && current->pDown != nullptr) //добавил условие справа
							{
								if (prev->pDown != current)
								{
									prev = prev->pDown;
								}
							}
						}
						else
						{
							current = current->pDown;
							if (prev->pNext != nullptr)
							{
								prev = prev->pNext;
							}
							else
							{
								prev = prev->pDown;
							}
						}
					}
					delete current;
					if (prev->pNext == nullptr)
					{
						prev->pDown = nullptr;
					}
					else
					{
						prev->pNext = nullptr;
					}
					//Print();
					continue;
				}
				Node* helper = head;
				delete head;
				helper = nullptr;
			}
		}
	}

	void Push_Back(string data)
	{
		int j = 0;
		while (j < data.length())
		{
			string str1 = string();
			while (j < data.length() && data[j] != '\n')
			{
				str1.push_back(data[j]);
				j++;
			}
			j++;
			if (head == nullptr)
			{
				NodeCounter++;
				int i = 0;
				bool proverka1 = true;
				while (i < str1.length())
				{
					string str = string();
					for (; i < str1.length(); i++)
					{
						if (str1[i] == '/')
						{
							i++;
							break;
						}
						str.push_back(str1[i]);
					}
					if (proverka1)
					{
						head = new Node(str);
						proverka1 = false;
					}
					else
					{
						Node* current = head;
						while (current->pDown != nullptr)
						{
							current = current->pDown;
						}
						current->pDown = new Node(str);
					}
				}
			}
			else
			{
				NodeCounter++;
				Node* current = head;
				while (current->pNext != nullptr)
				{
					current = current->pNext;
				}
				int i = 0;
				bool proverka2 = true;
				while (i < str1.length())
				{
					string str = string();
					for (; i < str1.length(); i++)
					{
						if (str1[i] == '/')
						{
							i++;
							break;
						}
						str.push_back(str1[i]);
					}
					if (proverka2)
					{
						current->pNext = new Node(str);
						proverka2 = false;
					}
					else
					{
						Node* current1 = current->pNext;
						while (current1->pDown != nullptr)
						{
							current1 = current1->pDown;
						}
						current1->pDown = new Node(str);
					}
				}
			}
		}
	}

	void Print()
	{
		Node* current = head;
		Node* current1 = head;
		while (current != nullptr)
		{
			while (current != nullptr)
			{
				cout << current->data << " ";
				current = current->pDown;
			}
			cout << endl;
			current1 = current1->pNext;
			current = current1;
		}
		//cout << current->data;
	}

	void Removing(string name)
	{
		bool iskeyNumber = true;
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] < '0' || name[i] > '9')
			{
				iskeyNumber = false;
			}
		}
		if (iskeyNumber)
		{
			int keyNumber = stoi(name);
			if (keyNumber < 0 || keyNumber > NodeCounter - 1)
			{
				cout << "¬ыход за массив" << endl;
				return void();
			}
			int i = 0;
			Node* prev = head;
			Node* current = head;
			while (i < NodeCounter)
			{
				if (i == keyNumber)
				{
					if (i == 0)
					{
						while (1)
						{
							if (head->pDown == nullptr)
							{
								break;
							}
							Node* current1 = head;
							Node* prev1 = head;
							while (current1->pDown != nullptr)
							{
								current1 = current1->pDown;
								if (current1->pDown != nullptr)
								{
									current1 = current1->pDown;
								}
								if (prev1->pDown != current1)
								{
									prev1 = prev1->pDown;
								}
							}
							delete current1;
							prev1->pDown = nullptr;
						}
						Node* temp = head;
						head = head->pNext;
						delete temp;
						return void();
					}
					else
					{
						while (1)
						{
							if (current->pDown == nullptr)
							{
								break;
							}
							Node* current2 = current;
							Node* prev2 = current;
							while (current2->pDown != nullptr)
							{
								current2 = current2->pDown;
								if (current2->pDown != nullptr)
								{
									current2 = current2->pDown;
								}
								if (prev2->pDown != current2)
								{
									prev2 = prev2->pDown;
								}
							}
							delete current2;
							prev2->pDown = nullptr;
						}
						Node* toDelete = current;
						prev->pNext = toDelete->pNext;
						delete toDelete;
						return void();
					}
				}
				current = current->pNext;
				if (current == nullptr)
				{
					cout << "“акого человека нет в списке!" << endl;
					return void();
				}
				if (prev->pNext != current)
				{
					prev = prev->pNext;
				}
				i++;
			}
			return void();
		}
		else
		{

			Node* current = head;
			Node* prev = head;
			while (current->data != name)
			{

				current = current->pNext;
				if (prev->pNext != current)
				{
					prev = prev->pNext;
				}

				if (current == nullptr)
				{
					cout << "“акого человека нет в списке!" << endl;
					return void();
				}
			}
			if (head->data == name)
			{
				while (1)
				{
					if (head->pDown == nullptr)
					{
						break;
					}
					Node* current1 = head;
					Node* prev1 = head;
					while (current1->pDown != nullptr)
					{
						current1 = current1->pDown;
						if (current1->pDown != nullptr)
						{
							current1 = current1->pDown;
						}
						if (prev1->pDown != current1)
						{
							prev1 = prev1->pDown;
						}
					}
					delete current1;
					prev1->pDown = nullptr;
				}
				Node* temp = head;
				head = head->pNext;
				delete temp;
			}
			else if (current->data == name)
			{
				while (1)
				{
					if (current->pDown == nullptr)
					{
						break;
					}
					Node* current2 = current;
					Node* prev2 = current;
					while (current2->pDown != nullptr)
					{
						current2 = current2->pDown;
						if (current2->pDown != nullptr)
						{
							current2 = current2->pDown;
						}
						if (prev2->pDown != current2)
						{
							prev2 = prev2->pDown;
						}
					}
					delete current2;
					prev2->pDown = nullptr;
				}
				Node* toDelete = current;
				prev->pNext = toDelete->pNext;
				delete toDelete;
			}
		}
	}

	void Finding(string name)
	{
		bool iskeyNumber = true;
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] < '0' || name[i] > '9')
			{
				iskeyNumber = false;
			}
		}
		if (iskeyNumber)
		{
			int keyNumber = stoi(name);
			if (keyNumber < 0 || keyNumber > NodeCounter - 1)
			{
				cout << "“акого человека нет в списке!" << endl;
				return void();
			}
			int i = 0;
			//Node* prev = head;
			Node* current = head;
			while (i < NodeCounter)
			{
				if (i == keyNumber)
				{
					if (i == 0)
					{
						cout << head->data << "/";
						while (current->pDown != nullptr)
						{
							current = current->pDown;
							if (current->pDown == nullptr)
							{
								cout << current->data;
							}
							else
							{
								cout << current->data << "/";
							}
						}
					}
					else
					{
						cout << current->data << "/";
						while (current->pDown != nullptr)
						{
							current = current->pDown;
							if (current->pDown == nullptr)
							{
								cout << current->data;
							}
							else
							{
								cout << current->data << "/";
							}
						}
					}
				}
				if (current->pNext == nullptr)
				{
					break;
				}
				current = current->pNext;
				//if (prev->pNext != current)
				//{
				//	prev = prev->pNext;
				//}
				i++;
			}
			return void();
		}
		else
		{

			Node* current = head;
			//Node* prev = head;
			while (current->data != name)
			{

				current = current->pNext;
				//if (prev->pNext != current)
				//{
				//	prev = prev->pNext;
				//}

				if (current == nullptr)
				{
					cout << "“акого человека нет в списке!" << endl;
					return void();
				}
			}
			if (head->data == name)
			{
				cout << head->data << "/";
				while (current->pDown != nullptr)
				{
					current = current->pDown;
					if (current->pDown == nullptr)
					{
						cout << current->data;
					}
					else
					{
						cout << current->data << "/";
					}
				}
			}
			else if (current->data == name)
			{
				cout << current->data << "/";
				while (current->pDown != nullptr)
				{
					current = current->pDown;
					if (current->pDown == nullptr)
					{
						cout << current->data;
					}
					else
					{
						cout << current->data << "/";
					}
				}
			}
			return void();
		}

	}

	void Sort()
	{
		Node* iCurrent = head;
		Node* jCurrent = head;
		for (int i = 0; i < NodeCounter; i++, iCurrent = iCurrent->pNext)
		{
			jCurrent = iCurrent->pNext;
			for (int j = i + 1; j < NodeCounter; j++, jCurrent = jCurrent->pNext)
			{
				if (iCurrent->data > jCurrent->data)
				{
					string helper = iCurrent->data;
					iCurrent->data = jCurrent->data;
					jCurrent->data = helper;

					Node* iCurrentDown = iCurrent;
					Node* jCurrentDown = jCurrent;
					while (iCurrentDown->pDown != nullptr)
					{
						iCurrentDown = iCurrentDown->pDown;
						jCurrentDown = jCurrentDown->pDown;

						helper = iCurrentDown->data;
						iCurrentDown->data = jCurrentDown->data;
						jCurrentDown->data = helper;
					}
				}
			}
		}
	}

	string operator[] (int index)
	{
		Node* current = head;
		int counter = 0;
		string person = string();
		while (current != nullptr)
		{
			if (counter == index)
			{
				Node* currentDown = current;
				while (currentDown != nullptr)
				{
					person += currentDown->data;
					currentDown = currentDown->pDown;
					if (currentDown != nullptr)
					{
						person += '/';
					}
				}

				return person;
			}
			counter++;
			current = current->pNext;
		}

	}

	int getSize()
	{
		return NodeCounter;
	}
};

class Table
{
public:
	virtual void insert(string str) = 0;
	virtual void find(string key) = 0;
	virtual void del(string key) = 0;
	//virtual void Prototype(Psevdo_HList& value) // Ќужна была чтобы мы увидили что дл€ всех ф-ций из класса предоставл€етс€ доступ к private пол€м Psevdo_HList
	//{
	//
	//}


protected:
	Psevdo_HList Phl;
};