#include <iostream>
#include <memory>

#include "BinTree.h"
#include "Figure.h"
#include "Rhomb.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Array.h"
#include "Criteria.h"

#define MAX_ARRAY_SIZE 3

using namespace std;

Figure* CreateFigure(char type);
Figure* FindInTree(Figure *figure, BinTree<Array<shared_ptr<Figure>>> &tree);
void RemoveFromTree(Figure *figure, BinTree<Array<shared_ptr<Figure>>> &tree);

const size_t memory_page_size = 65536;
const size_t block_size = std::max({ sizeof(Rhomb), sizeof(Pentagon), sizeof(Hexagon) });

Allocator Figure::allocator = Allocator(memory_page_size, block_size);

int main() {
	BinTree<Array<shared_ptr<Figure>>> tree;
	
	int count = 0;
	Array<shared_ptr<Figure>> *array = new Array<shared_ptr<Figure>>(MAX_ARRAY_SIZE);

	tree.Insert(array);

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
			if (count >= MAX_ARRAY_SIZE) {
				count = 0;
				array = new Array<shared_ptr<Figure>>(MAX_ARRAY_SIZE);
				(*array)[count] = shared_ptr<Figure>(CreateFigure(fig_type));
				tree.Insert(array);
				++count;
				continue;
			}
			(*array)[count] = shared_ptr<Figure>(CreateFigure(fig_type));
			++count;
		}
		else if (command == 'f') {
			cout << "Enter a figure <r/p/h> d1 (d2) to find" << endl;
			cin >> fig_type;
			if (fig_type != 'h' && fig_type != 'p' && fig_type != 'r')
				continue;
			Figure *temp_figure = CreateFigure(fig_type);

			temp_figure = FindInTree(temp_figure, tree);
			if (temp_figure != nullptr) {
				cout << "Found: " << endl;
				cout << *temp_figure << endl;
			}
			else {
				cout << "Nothing found" << endl;
			}
			//Figure::operator delete (temp_figure);
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
			cout << "Enter a figure <r/p/h> d1 (d2) to find" << endl;
			cin >> fig_type;
			if (fig_type != 'h' && fig_type != 'p' && fig_type != 'r')
				continue;
			Figure *temp_figure = CreateFigure(fig_type);
			RemoveFromTree(temp_figure, tree);
			cout << "Removed" << endl;
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
		fig = new Rhomb(std::cin);
	else if (type == 'p')
		fig = new Pentagon(std::cin);
	else if (type == 'h')
		fig = new Hexagon(std::cin);
	return fig;
}

Figure* FindInTree(Figure *figure, BinTree<Array<shared_ptr<Figure>>> &tree) {
	auto cur_it = tree.begin();
	auto end_it = tree.end();
	for (; cur_it != end_it; ++cur_it) {
		auto &cur_array = **cur_it;
		auto size = cur_array.Size();
		decltype(size) i = 0;
		for (; i < size; ++i) {
			if (*cur_array[i] == *figure) {
				return cur_array[i].get();
			}
		}
	}
}

void RemoveFromTree(Figure *figure, BinTree<Array<shared_ptr<Figure>>> &tree) {
	auto cur_it = tree.begin();
	auto end_it = tree.end();
	for (; cur_it != end_it; ++cur_it) {
		auto &cur_array = **cur_it;
		auto size = cur_array.Size();
		decltype(size) i = 0;
		for (; i < size; ++i) {
			if (cur_array[i] && *cur_array[i] == *figure) {
				cur_array.Remove(&cur_array[i]);
				return;
			}
		}
	}
}

void RemoveByCriteria(Figure *figure, BinTree<Array<shared_ptr<Figure>>> &tree) {
	auto cur_it = tree.begin();
	auto end_it = tree.end();
	for (; cur_it != end_it; ++cur_it) {
		auto &cur_array = **cur_it;
		auto size = cur_array.Size();
		decltype(size) i = 0;
		for (; i < size; ++i) {
			if (cur_array[i] && *cur_array[i] == *figure) {
				cur_array.Remove(&cur_array[i], Criteria cr&);
				return;
			}
		}
	}
}