#ifndef __BRBTREE_H__
#define __BRBTREE_H__
namespace std {
	enum class Color {
		Red,
		Black
	};

	template <typename T> class Node {
	private:
		T _value;
		Node<T>* _leftChild;
		Node<T>* _rightChild;
		Node<T>* _parent;
		Color _color;
	public:
		Node() {
			_leftChild = nullptr;
			_rightChild = nullptr;
			_parent = nullptr;
			_color = Color::Black;
		}

		Node(T value, Node<T>* parent, Node<T>* leaf) {
			_value = value;
			_leftChild = leaf;
			_rightChild = leaf;
			_parent = parent;
			_color = Color::Red;
		}

		T getValue() {
			return _value;
		}

		void setValue(T value) {
			_value = value;
		}

		Color getColor() {
			return _color;
		}

		void setColor(Color color) {
			_color = color;
		}

		Node<T>* getLeftChild() {
			return _leftChild;
		}

		void setLeftChild(Node<T>* leftChild) {
			_leftChild = leftChild;
			if (_leftChild != nullptr)
				_leftChild->setParent(this);
		}

		Node<T>* getRightChild() {
			return _rightChild;
		}

		void setRightChild(Node<T>* rightChild) {
			_rightChild = rightChild;
			if (_rightChild != nullptr)
				_rightChild->setParent(this);
		}

		Node<T>* getParent() {
			return _parent;
		}

		void setParent(Node<T>* parent) {
			_parent = parent;
		}

		void takePlaceOfParent() {
			Node<T>* parent = _parent;
			Node<T>* grandparent = _parent->getParent();

			_parent = grandparent;
			if (grandparent != nullptr) {
				if (_value < grandparent->getValue())
					grandparent->setLeftChild(this);
				else
					grandparent->setRightChild(this);
			}

			if (_value >= parent->getValue()) {
				parent->setRightChild(_leftChild);
				setLeftChild(parent);
			} else {
				parent->setLeftChild(_rightChild);
				setRightChild(parent);
			}
		}

		Node<T>* getMaxNode(Node<T>* leaf) {
			if (_rightChild == leaf)
				return this;
			return _rightChild->getMaxNode(leaf);
		}

		Node<T>* getMinNode(Node<T>* leaf) {
			if (_leftChild == leaf)
				return this;
			return _leftChild->getMinNode(leaf);
		}

		void print(Node<T>* root) {
			if (_leftChild == nullptr && _rightChild == nullptr)
				return;

			_leftChild->print(root);

			cout << _value;
			if (this == root)
				cout << "K";

			if (_color == Color::Red)
				cout << "R ";
			else
				cout << "B ";

			_rightChild->print(root);
		}

		int length() {
			if (_leftChild == nullptr && _rightChild == nullptr)
				return 0;
			return _leftChild->length() + _rightChild->length() + 1;
		}
	};

	template <typename T> class BRBTree {
	private:
		Node<T>* _leaf;
		Node<T>* _root;

		void switchNodeAndHisParent(Node<T>* node) {
			bool isParentRoot = node->getParent() == _root;
			node->takePlaceOfParent();
			if (isParentRoot)
				_root = node;
		}

		void balanceTreeAfterInsert(Node<T>* newNode) {
			if (newNode == _root) {
				newNode->setColor(Color::Black);
				return;
			}

			Node<T>* uncle;
			Node<T>* parent = newNode->getParent();
			Node<T>* grandparent = parent->getParent();
			while (parent->getColor() == Color::Red) {
				if (parent == grandparent->getLeftChild())
					uncle = grandparent->getRightChild();
				else
					uncle = grandparent->getLeftChild();

				if (uncle->getColor() == Color::Red) {
					parent->setColor(Color::Black);
					uncle->setColor(Color::Black);
					grandparent->setColor(Color::Red);
					newNode = grandparent;
				} else {
					if ((parent == grandparent->getLeftChild()) != (newNode == parent->getLeftChild())) {
						switchNodeAndHisParent(newNode);
						newNode = parent;
						parent = newNode->getParent();
						grandparent = parent->getParent();
					}
					parent->setColor(Color::Black);
					grandparent->setColor(Color::Red);
					switchNodeAndHisParent(parent);
				}

				if (newNode == _root)
					break;

				parent = newNode->getParent();
				grandparent = parent->getParent();
			}
			_root->setColor(Color::Black);
		}

		void balanceTreeAfterErase(Node<T>* node) {
			while (node != _root && node->getColor() == Color::Black) {
				Node<T>* brother;
				bool isBrotherRight = node->getParent()->getLeftChild() == node;
				if (isBrotherRight)
					brother = node->getParent()->getRightChild();
				else
					brother = node->getParent()->getLeftChild();

				if (brother->getColor() == Color::Red) {
					brother->setColor(Color::Black);
					node->getParent()->setColor(Color::Red);
					switchNodeAndHisParent(brother);
					
					if (isBrotherRight)
						brother = node->getParent()->getRightChild();
					else
						brother = node->getParent()->getLeftChild();
				}

				Node<T>* brotherLeftChild = brother->getLeftChild();
				Node<T>* brotherRightChild = brother->getRightChild();

				if (brotherLeftChild->getColor() == Color::Black && brotherRightChild->getColor() == Color::Black) {
					brother->setColor(Color::Red);
					node = brother->getParent();
				} else {
					Node<T>* brotherChildToCheck = isBrotherRight ? brotherRightChild : brotherLeftChild;
					Node<T>* brotherAnotherChild = isBrotherRight ? brotherLeftChild : brotherRightChild;

					if (brotherChildToCheck->getColor() == Color::Black) {
						brotherAnotherChild->setColor(Color::Black);
						brother->setColor(Color::Red);
						switchNodeAndHisParent(brotherAnotherChild);
						brother = brotherAnotherChild;
					}

					brother->setColor(brother->getParent()->getColor());
					brother->getParent()->setColor(Color::Black);
					if (isBrotherRight)
						brother->getRightChild()->setColor(Color::Black);
					else
						brother->getLeftChild()->setColor(Color::Black);
					switchNodeAndHisParent(brother);
					node = _root;
				}
			}
			node->setColor(Color::Black);
		}
	public:
		BRBTree() {
			_leaf = new Node<T>();
			_root = nullptr;
		}

		void print() {
			if (_root == nullptr) {
				cout << "Tree is empty" << endl;
				return;
			}

			_root->print(_root);
			cout << endl;
		}

		int length() {
			if (_root == nullptr)
				return 0;
			_root->length();
		}

		void insert(T value) {
			if (_root == nullptr) {
				_root = new Node<T>(value, nullptr, _leaf);
				balanceTreeAfterInsert(_root);
				return;
			}

			Node<T>* currentNode = _root;
			Node<T>* parent = nullptr;

			while (currentNode != _leaf) {
				parent = currentNode;
				if (value >= currentNode->getValue())
					currentNode = currentNode->getRightChild();
				else
					currentNode = currentNode->getLeftChild();
			}

			Node<T>* newNode = new Node<T>(value, parent, _leaf);
			if (value >= parent->getValue())
				parent->setRightChild(newNode);
			else
				parent->setLeftChild(newNode);
			balanceTreeAfterInsert(newNode);
		}

		void erase(T value) {
			if (_root == nullptr)
				return;

			Node<T>* currentNode = find(value);
			erase(currentNode);
		}

		void erase(Node<T>* node) {
			if (node == _leaf)
				return;

			Node<T>* leftChild = node->getLeftChild();
			Node<T>* rightChild = node->getRightChild();
			Node<T>* parent = node->getParent();
			Color nodeColor = node->getColor();

			if (leftChild == _leaf && rightChild == _leaf) {
				if (node == _root) {
					_root = nullptr;
					delete node;
					return;
				}

				if (parent->getLeftChild() == node)
					parent->setLeftChild(_leaf);
				else 
					parent->setRightChild(_leaf);
				
				delete node;
				if (nodeColor == Color::Black)
					balanceTreeAfterErase(_leaf);
				return;
			} 
			
			if (leftChild != _leaf && rightChild != _leaf) {
				Node<T>* nodeToReplace = leftChild->getMaxNode(_leaf);
				T value = nodeToReplace->getValue();
				erase(nodeToReplace);
				node->setValue(value);
				return;
			} 
			
			if (leftChild != _leaf) {
				if (node == _root) {
					_root = leftChild;
				} else {
					if (parent->getLeftChild() == node)
						parent->setLeftChild(leftChild);
					else
						parent->setRightChild(leftChild);
				}
				leftChild->setColor(Color::Black);
				delete node;
				return;
			} 
			
			if (rightChild != _leaf) {
				if (node == _root) {
					_root = rightChild;
				} else {
					if (parent->getLeftChild() == node)
						parent->setLeftChild(rightChild);
					else
						parent->setRightChild(rightChild);
				}
				rightChild->setColor(Color::Black);
				delete node;
			}
		}

		Node<T>* find(T value) {
			Node<T>* currentNode = _root;
			Node<T>* parent = nullptr;

			while (currentNode != _leaf && currentNode->getValue() != value) {
				parent = currentNode;
				if (value > currentNode->getValue())
					currentNode = currentNode->getRightChild();
				else
					currentNode = currentNode->getLeftChild();
			}

			return currentNode;
		}

		T getMax() {
			return _root->getMaxNode(_leaf)->getValue();
		}

		T getMin() {
			return _root->getMinNode(_leaf)->getValue();
		}
	};
}
#endif