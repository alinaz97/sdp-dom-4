
#include"Header.h"

template <typename T>
void insert(BinOrdTree<T> &tree, T p)
{
	tree.addNode(p);
	cout << "Record inserted!" << endl;
	

}

template <typename T>
void deleteStudent(BinOrdTree<T> &tree)
{
	long long search;
	cin >> search;
	tree.deleteNode(Student(search));
}

template <typename T>
void find(long long search, node<T>* root)
{
	if (!root)
	{
		return;
	}
	if (!root->left && !root->right) 
	{
		cout << "Record not found!" << endl;
	}
	else
	{
		if (root->data == search) cout << root->data << endl;
		else
		{
			find(search, root->left);
			find(search, root->right);
		}
	}
}


template <typename T>
void traverseInOrder(BinOrdTree<T> &tree)
{
	tree.print();
}

int main()
{
	BinOrdTree<Student> StudentDatabase;
	string command;
	cin >> command;
	do
	{
		if (command == "insert")
		{
			long long fn;
			string fname;
			string lname;
			cin >> fn;
			cin >> fname;
			cin >> lname;

			insert(StudentDatabase, Student (fn, fname, lname));
		}
		else if (command == "delete")
			deleteStudent(StudentDatabase);
		else if (command == "find")
		{
			long long search;
			cin >> search;
			node<Student>* p = StudentDatabase.getRootPtr();
			find(search, p);
		}
		else if (command == "traverseInOrder")
			traverseInOrder(StudentDatabase);

	} while (command != "exit");

	system("pause");
	return 0;


}