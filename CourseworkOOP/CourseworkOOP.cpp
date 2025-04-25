#include <iostream>
#include "BRBTree.h"
#include "BRBTreeInterface.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian_Russia.1251");

    BRBTree<int> tree;
    BRBTreeInterface<int> interface(tree);
    interface.start();

    system("pause");
}