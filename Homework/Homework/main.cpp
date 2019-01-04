#include<iostream>
#include<string>
#include "BinaryOrderTree.h"
using namespace std;
struct student { // structure for the data of the students in the binary file
	long long int fn;
	string name, familyName;

	friend ostream& operator<< (ostream&, student const&); // we predefine operator<< for outputting the faculty number of the student
};


bool flag; // flag for type of printing
ostream& operator<< (ostream& out, student const& st) {
	// we check the flag to see the type of printing - for the find function or for the traverseOrder function
	if (flag == true) out << st.fn << " " << st.name << " " << st.familyName << "\n";
	else out << st.fn;
	return out;
}


bool operator< (student const& lhs, student const& rhs) { // we predefine comparison operator for comparing students only by the faculty numbers in order to work in the binary ordered tree
	if (lhs.fn < rhs.fn) return true;
	return false;
}
bool operator> (student const& lhs, student const& rhs) { // we predefine comparison operator for comparing students only by the faculty numbers in order to work in the binary ordered tree
	if (lhs.fn > rhs.fn) return true;
	return false;
}
bool operator== (student const& lhs, student const& rhs) { // we predefine comparison operator for comparing students only by the faculty numbers in order to work in the binary ordered tree
	if (lhs.fn == rhs.fn) return true;
	return false;
}
int main() {
	string command; // variables for storing command and the first and last name respectively
	long long int fn; // variables for storing faculty number
	BinOrderTree<student> t; // tree for storing the students
	student st; // variable for the student
	for (;;) {
		cin >> command;
		if (command == "exit") break; // if command is exit, the program has to finish
		else if (command == "insert") { // if command is insert, we insert the student with the inputted data in the tree
			cin >> st.fn >> st.name >> st.familyName; // we input a student with faculty number and two names
			t.addNode(st);
			cout << "Record inserted!\n";
		}
		else if (command == "delete") { // if command is delete, we delete the student with inputted faculty number
			cin >> st.fn;
			st.name = st.familyName = ""; // we add empty names because the methods need student as a parameter
			t.deleteNode(st);
		}
		else if (command == "find") { // if command is find, we search the binary order tree for the inputted faculty number
			cin >> st.fn;
			flag = true; // setting flag for find function
			st.name = st.familyName = ""; // we add empty names because the methods need student as a parameter
			t.findNode(st);
		}
		else if (command == "traverseInorder") { // if command is traverseInorder, we traverse the binary order tree in inorder
			flag = false; // setting flag for traverseInorder function
			t.print();
		}
	}
	cout << endl;
	return 0;
}
