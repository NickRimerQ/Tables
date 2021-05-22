#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
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
					cout << "Такого человека нет в списке!" << endl;
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
				cout << "Такого человека нет в списке!" << endl;
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
					cout << "Такого человека нет в списке!" << endl;
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


int HashFunc(string key)
{
	int value = toupper(key[0]) - 'А' - 256 + (toupper(key[1]) - 'А' - 256) * 32;
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

			if (fullName.length() != 2 && str[i] >= 'А' && str[i] <= 'Я')
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
			if (fullName.length() != 2 && key[i] >= 'А' && key[i] <= 'Я')
			{
				fullName.push_back(key[i]);
			}
		}

		int index = HashFunc(fullName);
		table[index].push_back(key);
		return void();
	}

	virtual void find(string key)
	{
		string fullName = string();
		for (int i = 0; i < key.length(); i++)
		{
			if (fullName.length() != 2 && key[i] >= 'А' && key[i] <= 'Я')
			{
				fullName.push_back(key[i]);
			}
		}

		int index = HashFunc(fullName);
		if (table[index].size() == 0)
		{
			cout << "Такого человека нет в списке!" << endl;
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
		cout << "Такого человека нет в списке!" << endl;
		return void();
	}

	virtual void del(string key) override
	{
		string fullName = string();
		for (int i = 0; i < key.length(); i++)
		{
			if (fullName.length() != 2 && key[i] >= 'А' && key[i] <= 'Я')
			{
				fullName.push_back(key[i]);
			}
		}

		int index = HashFunc(fullName);
		if (table[index].size() == 0)
		{
			cout << "Такого человека нет в списке!" << endl;
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
		cout << "Такого человека нет в списке!" << endl;
		return void();
	}

};

class TreeTable : public ScanTable
{
	struct node
	{
		string key;
		string person;
		node* left;
		node* right;
		node(string key, string person)
		{
			this->key = key;
			this->person = person;
			left = right = NULL;
		}
	};

	enum chooser
	{
		INSERT,
		FIND,
		DELETE
	};

	chooser choice;

	node* head;


	void swaper(node* first, node* second)
	{
		swap(first->key, second->key);
		swap(first->person, second->person);
	}

	void commands(chooser choice, string key, node* ins = NULL)
	{
		switch (choice)
		{
		case TreeTable::INSERT:
		{

			if (head == NULL)
			{
				head = ins;
				return void();
			}

			node* current = head;
			while (true)
			{
				if (key > current->key)
				{
					if (current->right == NULL)
					{
						current->right = ins;
						break;
					}
					current = current->right;
				}
				else
				{
					if (current->left == NULL)
					{
						current->left = ins;
						break;
					}
					current = current->left;
				}
			}
			break;
		}
		case TreeTable::FIND:
		{

			node* current = head;

			while (current != NULL)
			{
				if (key > current->key)
				{
					current = current->right;
				}
				else if (key < current->key)
				{
					current = current->left;
				}
				else
				{
					cout << current->person << endl;
					return void();
				}
			}

			cout << "Такого человека нет в списке!" << endl;

			break;
		}
		case TreeTable::DELETE:
		{

			node* current = ins;
			while (ins != NULL)
			{
				if (key > ins->key)
				{
					//everything(choice, key, ins->right);
					ins = ins->right;
					if (current->right != NULL && ((current->right->right != NULL && current->right->right == ins) || (current->right->left != NULL && current->right->left == ins)))
					{
						current = current->right;
					}
					else if ((current->left != NULL && (current->left->right != NULL && current->left->right == ins) || (current->left->left != NULL && current->left->left == ins)))
					{
						current = current->left;
					}
					//current = current->right;
					//return void();
				}
				else if (key < ins->key)
				{
					//everything(choice, key, ins->left);
					ins = ins->left;
					if (current->right != NULL && ((current->right->right != NULL && current->right->right == ins) || (current->right->left != NULL && current->right->left == ins)))
					{
						current = current->right;
					}
					else if ((current->left != NULL && (current->left->right != NULL && current->left->right == ins) || (current->left->left != NULL && current->left->left == ins)))
					{
						current = current->left;
					}
					//return void();
					//current = current->left;
				}
				else
				{
					//node* currentHelper = current;

					if (ins->left == NULL && ins->right == NULL)
					{
						if (current->left == ins)
						{
							current->left = NULL;
						}
						else
						{
							current->right = NULL;
						}
						return void();
					}

					current = ins;

					if (current->right != NULL)
					{
						current = current->right;
					}

					while (current->left != NULL && current->right != NULL)
					{
						while (current->left != NULL)
						{
							current = current->left;
						}

						while (current->right != NULL)
						{
							current = current->right;
						}

					}

					swaper(ins, current);

					if (ins->right == current)
					{
						ins->right = NULL;
						return void();
					}

					if (ins->right != NULL)
					{
						ins = ins->right;
					}

					while (ins->left != NULL && ins->right != NULL)
					{
						while (ins->left != NULL)
						{
							if (ins->left == current)
							{
								ins->left = NULL;
								return void();
							}

							ins = ins->left;
						}

						while (ins->right != NULL)
						{
							if (ins->right == current)
							{
								ins->right = NULL;
								return void();
							}

							ins = ins->right;
						}

					}


				}
			}

			cout << "Такого человека нет в списке!" << endl;
			break;
		}
		}
	}

public:
	TreeTable()
	{
		for (int i = 0; i < Phl.getSize(); i++)
		{
			string key = string();
			string person = Phl[i];
			for (int j = 0; j < person.length(); j++)
			{
				if (person[j] == '/') break;
				key.push_back(person[j]);
			}

			node* ins = new node(key, person);

			commands(chooser::INSERT, key, ins);
		}
	}

	void insert(string str) override
	{
		string key = string();
		string person = str;
		for (int j = 0; j < person.length(); j++)
		{
			if (person[j] == '/') break;
			key.push_back(person[j]);
		}

		node* ins = new node(key, person);

		commands(chooser::INSERT, key, ins);
	}

	void find(string key) override
	{
		commands(chooser::FIND, key);
	}

	void del(string key) override
	{

		commands(chooser::DELETE, key, head);
	}

};

int main()
{
	setlocale(LC_ALL, "ru");


	//ScanTable a;
	//a.insert("Куматов Михаил/Англ 4/Матеша 5/Русский 2");
	//a.find("Куматов Михаил");
	//a.find("Петров Иван");
	//a.del("1");
	//a.del("Куматов Михаил");
	//a.find("Куматов Михаил");
	//a.find("Петров Иван");
	//a.Print();


	//SortTable a;
	//a.insert("Куматов Михаил/Англ 4/Матеша 5/Русский 2");
	//a.find("Куматов Михаил");

	//a.insert("АаАААов АААА/Англ 3/Матеша 4/Русский 7");
	//a.find("АаАААов АААА");

	//a.find("Петhров Иван");
	//a.del("Антонов Егор");
	//a.find("Антонов Егор");


	//cout << HashFunc("ЯЯ") << endl;

	//HashTable a;
	//a.find("Абрамов Евгений");
	//a.del("Абрамов Евгений");
	//a.find("Абрамов Евгений");
	//a.insert("Антонов Антон/Англ 3/Матеша 4/Русский 7");
	//a.find("Антонов Антон");


	//TreeTable a;
	//a.find("qwerty");
	//a.find("Петров Иван");

	//a.insert("antonov anton/Англ 4/Матеша 1/Русский 2");
	//a.find("antonov anton");

	//a.find("Абрамов Евгений");
	//a.del("Абрамов Евгений");
	//a.find("Абрамов Евгений");


	return 0;
}