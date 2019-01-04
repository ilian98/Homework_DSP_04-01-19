#ifndef BINARYORDERTREE_H_
#define BINARYORDERTREE_H_


#include<iostream>
using namespace std;


template <typename T>
struct TreeElement {
	T data;
	TreeElement<T> *left, *right;
};


template <typename T>
class BinOrderTree {
private:
	TreeElement<T>* root; // the root of the tree
	// private functions for use in the constructors and the destructors
	void deleteTree(TreeElement<T>* &) const;
	void copy(TreeElement<T>* &, TreeElement<T>* const&) const;
	void copyTree(BinOrderTree<T> const&);
	void printFromNode(TreeElement<T> const*, bool&) const;

	// private functions for use in add, delete and find functions
	void add(TreeElement<T>* &, T const&) const;
	void deleteNodePtr(TreeElement<T>* &, T const&) const;
	void findNodePtr(TreeElement<T>* &, T const&) const;
public:
	// the big 4 for the class
	BinOrderTree();
	BinOrderTree(BinOrderTree<T> const&);
	BinOrderTree<T>& operator=(BinOrderTree<T> const&);
	~BinOrderTree();

	// public functions for accessing root data and pointer to root
	T getRootData() const;
	TreeElement<T>* getRootPtr() const;

	// public functions for accessing left and right tree
	BinOrderTree<T> leftTree() const;
	BinOrderTree<T> rightTree() const;

	// public functions for checking if a tree is empty and to print the tree
	bool empty() const;
	void print() const;

	// public functions for adding, deleting and finding tree element
	void addNode(T const&);
	void deleteNode(T const&);
	void findNode(T const&);

	// public functions for making tree with root, left and right tree
	void createWithData(T const&, BinOrderTree<T> const&, BinOrderTree<T> const&);
};


template <typename T>
void BinOrderTree<T>::deleteTree(TreeElement<T>*& t) const {
	if (t == NULL) return;
	deleteTree(t->left); deleteTree(t->right);
	delete t;
	t = NULL;
}
template <typename T>
void BinOrderTree<T>::copy(TreeElement<T>*& to, TreeElement<T>* const& from) const {
	if (from == NULL) {
		to = from;
		return;
	}
	to = new TreeElement<T>;
	to->data = from->data;
	copy(to->left, from->left);
	copy(to->right, from->right);
}
template <typename T>
void BinOrderTree<T>::copyTree(BinOrderTree<T> const& t) {
	copy(root, t.root);
}
template <typename T>
void BinOrderTree<T>::printFromNode(TreeElement<T> const* t, bool& flag) const { // flag for knowing the first faculty that will be printed
	if (t == NULL) return;
	printFromNode(t->left, flag);
	if (flag != 1) cout << ", ";
	cout << t->data;
	flag = 0;
	printFromNode(t->right, flag);
}


template <typename T>
void BinOrderTree<T>::add(TreeElement<T>*& t, T const& data) const {
	if (t == NULL) {
		t = new TreeElement<T>;
		t->data = data;
		t->left = t->right = NULL;
		return;
	}
	if (t->data == data) {
		t->data = data;
		return;
	}
	if (t->data > data) add(t->left, data);
	else add(t->right, data);
}
template <typename T>
void BinOrderTree<T>::deleteNodePtr(TreeElement<T>*& t, T const& data) const {
	if (t == NULL) {
		cout << "Record not found!\n";
		return;
	}
	TreeElement<T>* temp;
	if (t->data == data) {
		if (t->left == NULL) {
			temp = t;
			t = t->right;
			delete temp;
			cout << "Record deleted!\n";
			return;
		}
		if (t->right == NULL) {
			temp = t;
			t = t->left;
			delete temp;
			cout << "Record deleted!\n";
			return;
		}
		temp = t->right;
		for (;;) {
			if (temp->left == NULL) break;
			temp = temp->left;
		}
		t->data = temp->data;
		deleteNodePtr(t->right, temp->data);
		cout << "Record deleted!\n";
		return;
	}
	if (t->data > data) deleteNodePtr(t->left, data);
	else deleteNodePtr(t->right, data);
}
template <typename T>
void BinOrderTree<T>::findNodePtr(TreeElement<T>*& t, T const& data) const {
	if (t == NULL) {
		cout << "Record not found!\n";
		return;
	}
	if (t->data == data) {
		cout << t->data;
		return;
	}
	if (t->data > data) findNodePtr(t->left, data);
	else findNodePtr(t->right, data);
}


template <typename T>
BinOrderTree<T>::BinOrderTree() {
	root = NULL;
}
template <typename T>
BinOrderTree<T>::BinOrderTree(BinOrderTree<T> const& rhs) {
	copyTree(rhs);
}
template <typename T>
BinOrderTree<T>& BinOrderTree<T>::operator= (BinOrderTree<T> const& rhs) {
	if (this == &rhs) return *this;
	deleteTree(root);
	copyTree(rhs);
	return *this;
}
template <typename T>
BinOrderTree<T>::~BinOrderTree() {
	deleteTree(root);
}


template <typename T>
T BinOrderTree<T>::getRootData() const {
	return root->data;
}
template <typename T>
TreeElement<T>* BinOrderTree<T>::getRootPtr() const {
	return root;
}


template <typename T>
BinOrderTree<T> BinOrderTree<T>::leftTree() const {
	BinOrderTree<T> t;
	copy(t.root, root->left);
	return t;
}
template <typename T>
BinOrderTree<T> BinOrderTree<T>::rightTree() const {
	BinOrderTree<T> t;
	copy(t.root, root->right);
	return t;
}


template <typename T>
bool BinOrderTree<T>::empty() const {
	if (root == NULL) return true;
	return false;
}
template <typename T>
void BinOrderTree<T>::print() const {
	bool flag = 1;
	printFromNode(root, flag);
	cout << "\n";
}


template <typename T>
void BinOrderTree<T>::addNode(T const& data) {
	add(root, data);
}
template <typename T>
void BinOrderTree<T>::deleteNode(T const& data) {
	deleteNodePtr(root, data);
}
template <typename T>
void BinOrderTree<T>::findNode(T const& data) {
	findNodePtr(root, data);
}


template <typename T>
void BinOrderTree<T>::createWithData(T const& data, BinOrderTree<T> const& left, BinOrderTree<T> const& right) {
	root = new TreeElement<T>;
	root->data = data;
	copy(root->left, left.root); copy(root->right, right.root);
}



#endif
