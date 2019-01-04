#pragma once
#pragma warning(disable: 4996)
#include<fstream>
#include<iostream>
#include<string>


using namespace std;
const int NAME_LENGHT = 256;
const long long FN_SIZE = 1125899906842624;

class Student
{
protected:
	long long fn;
	string first_name;
	string last_name;

public:

	Student(const long long _fn = 0, const string _first_name =NULL, const string _last_name = NULL): fn(_fn)
	{
		first_name.assign(_first_name);
		last_name.assign(_last_name);
	};


	Student& operator=(const Student& other)
	{
		if (this != &other)
		{
			fn = other.fn;
			first_name.assign(other.first_name);
			last_name.assign(other.last_name);


		}
		return *this;
	}
	
	friend bool operator==(const Student l, const Student r);
	friend bool operator > (const Student& l, const Student& r);
	friend bool operator < (const Student& l, const Student& r);
	friend ostream& operator << (ostream &out, const Student &p);
	
};

bool operator==(const Student l, const Student r)
{
	return l.fn == r.fn;
}

bool operator<(const Student& l, const Student& r)
{
	return l.fn < r.fn;
}

bool operator>(const Student& l, const Student& r)
{
	return l.fn > r.fn;
}

ostream& operator<<(ostream &out, const Student &p)
{
	out << p.fn << " " << p.first_name << " " << p.last_name;
	return out;
}


template <typename T>
struct node {
	T data;
	node<T> *left;
	node<T> *right;

	friend ostream& operator << (ostream& out, node<T> p);
	friend istream& operator >> (istream& in, node<T> p);
};
template <typename T>
ostream& operator << (ostream& out, node<T> p)
{
	out << p.data;
	return out;
}

template <typename T>
istream& operator >> (istream& in, node<T> p)
{
	in >> p.data;
	return in;
}

template <typename T>
class BinOrdTree 
{
private:

	node<T> *root;
	void copy(node<T> * &, node<T> * const &) const;
	void copyTree(BinOrdTree const &);
	void printFromNode(const node<T> *) const;
	void add(node<T> * &, T const &) const;

public:

	BinOrdTree();
	~BinOrdTree();
	BinOrdTree(BinOrdTree const &);
	BinOrdTree& operator=(BinOrdTree const &);
	T getRootData() const;
	node<T>* getRootPtr() const;
	BinOrdTree leftTree() const;
	BinOrdTree rightTree() const;
	bool empty()const;
	void print() const;
	void addNode(T const &);
	void deleteNode(T const &);
	void deleteNodePtr(node<T> * &, const T &);
	void deleteTree(node<T>* &) const;
	void createWithData(T, BinOrdTree, BinOrdTree);
	void create();
	void minTree( T &, BinOrdTree &) const;
};

template <typename T>
BinOrdTree<T>::BinOrdTree() {
	root = NULL;
}

template <typename T>
BinOrdTree<T>::~BinOrdTree() {
	deleteTree(root);
}

template <typename T>
BinOrdTree<T>::BinOrdTree(BinOrdTree<T> const &tree) {
	copyTree(tree);
}

template <typename T>
BinOrdTree<T>& BinOrdTree<T>::operator=(BinOrdTree<T> const &tree)
{
	if (this != &tree) {
		deleteTree(root);
		copyTree(tree);
	}
	return *this;
}

template <typename T>
void BinOrdTree<T>::deleteTree(node<T>* &treeRoot) const
{
	if (!treeRoot) {
		return;
	}
	deleteTree(treeRoot->left);
	deleteTree(treeRoot->right);
	delete treeRoot;
	treeRoot = NULL;
}

template <typename T>
void BinOrdTree<T>::copyTree(BinOrdTree<T> const & tree) {
	copy(root, tree.root);
}

template <typename T>
void BinOrdTree<T>::copy(node<T>* &dest, node<T> * const &src) const {
	dest = NULL;
	if (src) {
		dest = new node<T>;
		dest->data = src->data;
		copy(dest->left, src->left);
		copy(dest->right, src->right);
	}
}

template <typename T>
bool BinOrdTree<T>::empty() const {
	return root == NULL;
}

template <typename T>
T BinOrdTree<T>::getRootData() const {
	return root->data;
}

template <typename T>
node<T>* BinOrdTree<T>::getRootPtr() const {
	return root;
}

template <typename T>
BinOrdTree<T> BinOrdTree<T>::leftTree() const {
	BinOrdTree copiedTree;
	copy(copiedTree.root, root->left);
	return copiedTree;
}

template <typename T>
BinOrdTree<T> BinOrdTree<T>::rightTree() const {
	BinOrdTree copiedTree;
	copy(copiedTree.root, root->right);
	return copiedTree;
}

template <typename T>
void BinOrdTree<T>::printFromNode(const node<T> *treeNode) const {
	if (!treeNode) {
		return;
	}
	printFromNode(treeNode->left);
	cout << treeNode->data << ", ";
	printFromNode(treeNode->right);
}


template <typename T>
void BinOrdTree<T>::add(node<T> * &treeNode, T const &x) const 
{
	if (!treeNode) {
		treeNode = new node<T>;
		treeNode->data = x;
		treeNode->left = NULL;
		treeNode->right = NULL;
		return;
	}
	if (x < treeNode->data) {
		add(treeNode->left, x);
	}
	else {
		add(treeNode->right, x);
	}
}

template <typename T>
void BinOrdTree<T>::addNode(T const &x) {
	add(root, x);
}

template <typename T>
void BinOrdTree<T>::create() {
	root = NULL;
	T nodeValue; 
	do {
		cin >> nodeValue;
		addNode(nodeValue);
	} while (cin);
}

template <typename T>
void BinOrdTree<T>::createWithData(T x,BinOrdTree<T> left, BinOrdTree<T> right) {
	root = new node<T>;
	root->data = x;
	copy(root->left, left.root);
	copy(root->right, right.root);
}

template <typename T>
void BinOrdTree<T>::minTree(T &x, BinOrdTree<T> &mint) const {
	T a = getRootData();
	if (!root->left) {
		x = a;
		mint = rightTree();
	}
	else {
		BinOrdTree<T> updatedLeftTree;
		leftTree().minTree(x, updatedLeftTree);
		mint.createWithData(a, updatedLeftTree, rightTree());
	}
}

template <typename T>
void BinOrdTree<T>::deleteNode(T const &x) {
	if (!root) {
		return;
	}
	T a = getRootData();
	BinOrdTree<T> tempTree;
	if (a == x && !root->left) {
		*this = this->rightTree();
		return;
	}
	if (a == x && !root->right) {
		*this = leftTree();
		return;
	}
	if (a == x) {
		T rootValue;
		rightTree().minTree(rootValue, tempTree);
		createWithData(rootValue, leftTree(), tempTree);
		return;
	}
	tempTree = *this;
	if (x < a) {
		*this = leftTree();
		deleteNode(x);
		createWithData(a, *this, tempTree.rightTree());
		return;
	}
	if (x > a) {
		*this = rightTree();
		deleteNode(x);
		createWithData(a, tempTree.leftTree(), *this);
	}
}

template <typename T>
void BinOrdTree<T>::deleteNodePtr(node<T> * &root, const T &x) {
	if (!root) return;
	if (x < root->data) {
		deleteNodePtr(root->left, x);
	}
	else if (x > root->data) {
		deleteNodePtr(root->right, x);
	}
	else {
		node<T> *tempPtr;
		if (!(root->left)) {
			tempPtr = root; root = root->right;
			delete tempPtr;
		}
		else if (!(root->right)) {
			tempPtr = root;
			root = root->left;
			delete tempPtr;
		}
		else {
			tempPtr = root->right;
			while (tempPtr->left) {
				tempPtr = tempPtr->left;
			}
			root->data = tempPtr->data;
			deleteNodePtr(root->right, tempPtr->data);
		}
	}
}

template <typename T>
void BinOrdTree<T>::print() const {
	printFromNode(root);
}