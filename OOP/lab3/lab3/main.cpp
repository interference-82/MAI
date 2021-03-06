#include <iostream>
#include <memory>

#include "BinaryTree.h"
#include "Figure.h"
#include "Rhomb.h"
#include "Pentagon.h"
#include "Hexagon.h"

using namespace std;

int main()
{
	shared_ptr<Figure> r(new Rhomb(2, 5));
	shared_ptr<Figure> p(new Pentagon(39));
	shared_ptr<Figure> h(new Hexagon(5));

	cout << r->Square() << endl;
	cout << p->Square() << endl;
	cout << h->Square() << endl;

	BinaryTree tree;

	tree.Insert(r);
	tree.Insert(p);

	tree.Insert(h);

	tree.Print();
	cout << "-----" << endl;

	cout << *(tree.Find(shared_ptr<Figure>(new Rhomb(5, 2))));
	tree.Erase(r);
	tree.Erase(p);

	cout << "-----" << endl;

	cout << tree;

	system("pause");

    return 0;
}