#include <iostream>
#include "BRBTree.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian_Russia.1251");

    BRBTree<int> tree;
    tree.insert(7);
    tree.insert(8);
    tree.insert(5);
    tree.insert(9);
    tree.insert(3);
    tree.insert(6);
    tree.insert(4);

    tree.print();
    cout << tree.getMin() << " " << tree.getMax() << endl;

    tree.erase(5);
    tree.print();

    system("pause");
}