#include <iostream>
#include <memory>

#include "BinTree.h"
#include "Figure.h"
#include "Rhomb.h"
#include "Pentagon.h"
#include "Hexagon.h"

using namespace std;

Figure* CreateFigure(char);

int main()
{
	BinTree<Figure> tree;
	
	char command = 0;
	char fig_type = 0;

	while (1) {
		cout << "Enter a command <a/f/r/p/h/i>" << endl;
		cin >> command;
		if (cin.eof())
			break;
		if (command == 'a') {
			cout << "Enter a figure <r/p/h> d1 (d2) to insert" << endl;
			cin >> fig_type;
			if (fig_type != 'h' && fig_type != 'p' && fig_type != 'r')
				continue;
			tree.Insert(CreateFigure(fig_type));
		}
		else if (command == 'f') {
			cout << "Enter a figure <r/p/h> d1 (d2) to find" << endl;
			cin >> fig_type;
			if (fig_type != 'h' && fig_type != 'p' && fig_type != 'r')
				continue;
			Figure *temp_figure = CreateFigure(fig_type);
			auto temp = tree.Find(*temp_figure);
			if (temp == tree.end())
				cout << "Nothing found" << endl;
			else
				cout << "Found: " << **temp << endl;
			delete temp_figure;
		}
		else if (command == 'p') {
			cout << "Current state of the tree: " << endl;
			tree.Print();
		}
		else if (command == 'e') {
			break;
		}
		else if (command == 'i') {
			cout << "inorder print: " << endl;
			for (auto el : tree)
				cout << *el << ' ';
			cout << endl;
		}
		else if (command == 'r') {
			cout << "Enter a figure <r/p/h> d1 (d2) to remove" << endl;
			cin >> fig_type;
			if (fig_type != 'h' && fig_type != 'p' && fig_type != 'r')
				continue;
			Figure *temp_figure = CreateFigure(fig_type);
			tree.Remove(*temp_figure);
			delete temp_figure;
		}
		else if (command == 'h') {
			cout <<
				R"(commands:
	a -- add,
	f -- find
	r -- remove,
	p -- print,
	h -- help,
	i -- inorder print.
figures:
	p l -- pentgon by length of side,
	h l -- hexagon by length of side,
	r d1 d2 -- rhomb by two diagonals d1, d2.)" << endl;
		}
	}
}

Figure* CreateFigure(char type) {
	Figure *fig = nullptr;
	if (type == 'r')
		fig = new Rhomb(cin);
	else if (type == 'p')
		fig = new Pentagon(cin);
	else if (type == 'h')
		fig = new Hexagon(cin);
	return fig;
}