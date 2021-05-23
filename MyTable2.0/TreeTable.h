#pragma once
#include "ScanTable.h"


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


	void swap_of_leaves(node* first, node* second)
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

					swap_of_leaves(ins, current);

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
