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

public:
	Psevdo_HList()
	{
		head = nullptr;
	}

	~Psevdo_HList()
	{
		if (head != nullptr)
		{
			while(1)
			{
				if(head->pDown == nullptr && head->pNext == nullptr)
				{
					break;
				}
				Node* current = head;
				Node* prev = head;

				while(current->pNext != nullptr)
				{
					current = current->pNext;
					if(current->pNext != nullptr)
					{
						prev = prev->pNext;
					}
				}
				int k = 0;
				while(current->pDown != nullptr)
				{
					if(prev == head && current == head)
					{
						current = current->pDown;
						if(current->pDown != nullptr)
						{
							current = current->pDown;
						}
						if(prev->pNext == nullptr && current->pDown != nullptr) //добавил условие справа
						{
							prev = prev->pDown;
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
							//cout << prev->data << endl;
							prev = prev->pDown;
						}
					}
				}
				//Print();
				delete current;
				if(prev->pNext == nullptr)
				{
					//cout << "1 " << prev->data << endl;
					prev->pDown = nullptr;
				}
				else
				{
					//cout << "2 " << endl;
					prev->pNext = nullptr;
				}
				continue;

				//if (current->pDown != nullptr)
				//{
				//	current = current->pDown;
				//	if(prev->pNext != nullptr) //оно и не будет равно nullptr(костыль?)
				//	{
				//		prev = prev->pNext;
				//	}	 
				//}
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
			while (j < data.length() && data[j] != '\n' )
			{
				str1.push_back(data[j]);
				j++;
			}
			j++;
			if (head == nullptr)
			{
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
		while(current != nullptr)
		{
			while(current != nullptr)
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
};

class Table
{
public:
	Table();
	~Table();
	virtual void insert(string str) = 0;
	virtual string find(string key) = 0;
	virtual bool del(string key) = 0;
	//virtual void Prototype(Psevdo_HList& value) // Нужна была чтобы мы увидили что для всех ф-ций из класса предоставляется доступ к private полям Psevdo_HList
	//{
	//	
	//}

protected:
	Psevdo_HList Phl;
};



int main()
{
	setlocale(LC_ALL, "ru");

	//cout << TableReading() << endl;
	Psevdo_HList a;
	a.Push_Back(TableReading());
	
	a.Print();

	return 0;
}