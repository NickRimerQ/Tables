#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string TableReading()
{
	string path = "MyFile.txt";
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
				cout << "Выход за массив" << endl;
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

						head = head->pNext;
						delete current;
						return void();
					}
					prev->pNext = current->pNext;
					delete current;
					return void();
				}
				current = current->pNext;
				if (current == nullptr)
				{
					cout << "net чела" << endl;
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
					cout << "Такого человека нет в списке!" << endl;
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

	}
};

class Table
{
public:
	virtual void insert(string str) = 0;
	virtual void find(string key) = 0;
	virtual void del(string key) = 0;
	//virtual void Prototype(Psevdo_HList& value) // Нужна была чтобы мы увидили что для всех ф-ций из класса предоставляется доступ к private полям Psevdo_HList
	//{
	//	
	//}

protected:
	Psevdo_HList Phl;
};


class ScanTable : public Table
{
public:
	ScanTable()
	{
		Phl.Push_Back(TableReading());
		Phl.Print();
		cout << "---------------------------------------" << endl;
	}
	void insert(string str) override
	{
		Phl.Push_Back(str);
		Phl.Print();
	}
	void find(string key) override
	{
		
	}
	void del(string key) override
	{
		Phl.Removing(key);
		Phl.Print();
	}
};



int main()
{
	setlocale(LC_ALL, "ru");

	////cout << TableReading() << endl;
	//Psevdo_HList a;
	//a.Push_Back(TableReading());

	//a.Print();
	//cout << "---------------------------------------" << endl;
	//a.Removing("Захаров Алексей");
	//a.Removing("2");
	//a.Print();

	ScanTable a;
	//a.del("2");
	a.insert("Куматов Михаил/Англ 4/Матеша 5/Русский 2");

	return 0;
}