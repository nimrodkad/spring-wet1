
#include <iostream>
using namespace std;
#include "../AVLtree.h"
#include "../utils.h"

class Comp{
public:
    bool operator() (int* a, int* b)
    {
        return *a < *b ? true : false;
    }

    bool operator() (double* a, double* b)
    {
        return *a < *b ? true : false;
    }
};


int main() {
	AVLtree<int, int, Comp> tree1;
	int n=7;
	tree1.insert(&n,NULL);
	n=3;
    tree1.insert(&n,NULL);
	n=5;
	tree1.insert(&n,NULL);
	n=10;
	tree1.print();
	cout << endl;
	tree1.insert(&n,NULL);
	n=4;
	tree1.print();
	cout << endl;
	tree1.insert(&n,NULL);
	n=1;
	tree1.print();
	cout << endl;
	tree1.insert(&n,NULL);
	n=23;
	tree1.print();
	cout << endl;
	tree1.insert(&n,NULL);
	tree1.print();
	cout << endl;

	// RL and RR checks mostly
	AVLtree<double, double, Comp> tree3;
	double m=2;
	tree3.insert(&m,NULL);
	m=3;
	tree3.insert(&m,NULL);
	m=1;
	tree3.insert(&m,NULL);
	m=8;
	tree3.insert(&m,NULL);
	m=7;
	tree3.insert(&m,NULL);
	m=6;
	tree3.insert(&m,NULL);
	m=5;
	tree3.insert(&m,NULL);
	m=12;
	tree3.insert(&m,NULL);
	m=10;
	tree3.insert(&m,NULL);
	m=9;
	tree3.insert(&m,NULL);
	m=9.5;
	tree3.insert(&m,NULL);
	m=11;
	tree3.insert(&m,NULL);
	m=13;
	tree3.insert(&m,NULL);
	tree3.print();
	cout << endl;

	// LR and LL checks mostly
	AVLtree<double, double, Comp> tree4;
	m=8;
	tree4.insert(&m,NULL);
	m=5;
	tree4.insert(&m,NULL);
	m=3;
	tree4.insert(&m,NULL);
	m=4;
	tree4.insert(&m,NULL);
	m=4.5;
	tree4.insert(&m,NULL);
	m=7;
	tree4.insert(&m,NULL);
	m=6;
	tree4.insert(&m,NULL);
	m=2;
	tree4.insert(&m,NULL);
	m=2.5;
	tree4.insert(&m,NULL);
	m=3.5;
	tree4.insert(&m,NULL);
	tree4.print();
	cout << endl;

	AVLtree<double, double, Comp> tree2;
	m=4;
	tree2.insert(&m,NULL);
	m=2;
	tree2.insert(&m,NULL);
	m=3;
	tree2.insert(&m,NULL);
	m=1;
	tree2.insert(&m,NULL);
	m=8;
	tree2.insert(&m,NULL);
	m=7;
	tree2.insert(&m,NULL);
	m=6;
	tree2.insert(&m,NULL);
	m=5;
	tree2.insert(&m,NULL);
	m=12;
	tree2.insert(&m,NULL);
	m=10;
	tree2.insert(&m,NULL);
	m=9;
	tree2.insert(&m,NULL);
	m=9.5;
	tree2.insert(&m,NULL);
	m=11;
	tree2.insert(&m,NULL);
	m=13;
	tree2.insert(&m,NULL);
	tree2.print();
	cout << endl;

	// remove node with no children - no rotation
	m=8;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with one child - no rotation
	m=9;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with one child - no rotation
	m=2;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with two children - no rotation
	m=3;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with no children - with 1 rotation
	m=9.5;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with no children - with 1 rotation
	m=13;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with no children - no rotation
	m=10;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with two children - no rotation
	m=4;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with two children - no rotation
	m=5;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with no children - no rotation
	m=12;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove node with one child - no rotation
	m=6;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove root with two children - no rotation
	m=7;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove root with one child - no rotation
	m=11;
	tree2.remove(&m);
	tree2.print();
	cout << endl;
	// remove root with no children - no rotation
	m=1;
	tree2.remove(&m);
	m=12;
	tree2.insert(&m, NULL);
	tree2.print();
	cout << endl;
	m=12;
	tree2.remove(&m);

	// after removal - 2 rotations
	AVLtree<int, int, Comp> tree5;
	n=9;
	tree5.insert(&n, NULL);
	n=3;
	tree5.insert(&n, NULL);
	n=15;
	tree5.insert(&n, NULL);
	n=1;
	tree5.insert(&n, NULL);
	n=7;
	tree5.insert(&n, NULL);
	n=13;
	tree5.insert(&n, NULL);
	n=19;
	tree5.insert(&n, NULL);
	n=5;
	tree5.insert(&n, NULL);
	n=11;
	tree5.insert(&n, NULL);
	n=17;
	tree5.insert(&n, NULL);
	n=21;
	tree5.insert(&n, NULL);
	n=23;
	tree5.insert(&n, NULL);
	tree5.print();
	cout << endl;

    n=1;
	tree5.remove(&n);
	tree5.print();
	cout << endl;

	return 0;
}

