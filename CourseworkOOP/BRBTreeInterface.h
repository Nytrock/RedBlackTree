#ifndef __BRBTREEINTERFACE_H__
#define __BRBTREEINTERFACE_H__
#include "BRBTree.h"

namespace std {
	template <typename T> class BRBTreeInterface {
	private:
		BRBTree<T> _tree;

		void printTree() {
			cout << "Tree look like this:" << endl;
			_tree.print();
			cout << "Tree length: " << _tree.length() << endl;
			cout << endl;
		}

		void printMenu() {
			cout << "Choose action" << endl;
			cout << "1 — Insert" << endl;
			cout << "2 — Erase" << endl;
			cout << "3 — Get min" << endl;
			cout << "4 — Get max" << endl;
			cout << "5 — Exit" << endl;
		}

		void insertValue() {
			cout << "Enter value to insert: ";
			T value;
			cin >> value;
			_tree.insert(value);
		}

		void eraseValue() {
			cout << "Enter value to erase: ";
			T value;
			cin >> value;
			_tree.erase(value);
		}

		void getMin() {
			if (_tree.length() == 0)
				cout << "Tree is empty and don't have min value" << endl;
			else
				cout << "Min value is: " << _tree.getMin() << endl;
			waitForEnter();
		}

		void getMax() {
			if (_tree.length() == 0)
				cout << "Tree is empty and don't have max value" << endl;
			else
				cout << "Max value is: " << _tree.getMax() << endl;
			waitForEnter();
		}

		void waitForEnter() {
			cout << "Press enter to continue" << endl;
			cin.ignore();
			cin.ignore();
		}
	public:
		BRBTreeInterface(BRBTree<T> tree) {
			_tree = tree;
		}

		void start() {
			while (true) {
				system("cls");
				printTree();
				printMenu();

				int action;
				cin >> action;

				switch (action) {
					case 1: insertValue(); break;
					case 2: eraseValue(); break;
					case 3: getMin(); break;
					case 4: getMax(); break;
					case 5: return;
				}
			}
			system("pause");
		}
	};
}
#endif