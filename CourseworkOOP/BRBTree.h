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
		Node(T value, Node<T>* parent) {
			_value = value;
			_leftChild = nullptr;
			_rightChild = nullptr;
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
		}

		Node<T>* getRightChild() {
			return _rightChild;
		}

		void setRightChild(Node<T>* rightChild) {
			_rightChild = rightChild;
		}

		Node<T>* getParent() {
			return _parent;
		}

		void setParent(Node<T>* parent) {
			_parent = parent;
		}

		void takePlaceOfParent() {

		}

		Node<T>* getMaxNode() {
			if (_rightChild == nullptr)
				return this;
			return _rightChild->getMaxNode();
		}

		Node<T>* getMinNode() {
			if (_leftChild == nullptr)
				return this;
			return _leftChild->getMinNode();
		}

		void print() {
			cout << _value << " ";
			if (_leftChild != nullptr)
				_leftChild->print();
			if (_rightChild != nullptr)
				_rightChild->print();
		}
	};

	template <typename T> class BRBTree {
	private:
		Node<T>* _root = nullptr;

		void balanceTreeAfterInsert(Node<T>* newNode) {

		}

		void balanceTreeAfterErase(Node<T>* erasedNodeBrother) {

		}
	public:
		void print() {
			_root->print();
			cout << endl;
		}

		void insert(T value) {
			if (_root == nullptr) {
				_root = new Node<T>(value, nullptr);
				return;
			}

			Node<T>* currentNode = _root;
			Node<T>* parent = nullptr;

			while (currentNode != nullptr) {
				parent = currentNode;
				if (value > currentNode->getValue())
					currentNode = currentNode->getRightChild();
				else
					currentNode = currentNode->getLeftChild();
			}

			Node<T>* newNode = new Node<T>(value, parent);
			if (value > parent->getValue())
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
			if (node == nullptr)
				return;

			Node<T>* leftChild = node->getLeftChild();
			Node<T>* rightChild = node->getRightChild();
			Node<T>* parent = node->getParent();
			bool isNodeLeft = parent->getLeftChild() == node;

			if (leftChild == nullptr && rightChild == nullptr) {
				Node<T>* brother;
				Color nodeColor = node->getColor();

				if (isNodeLeft) {
					brother = parent->getRightChild();
					parent->setLeftChild(nullptr);
				} else {
					brother = parent->getLeftChild();
					parent->setRightChild(nullptr);
				}

				delete node;
				if (nodeColor == Color::Black)
					balanceTreeAfterErase(brother);
				return;
			} 
			
			if (leftChild != nullptr && rightChild != nullptr) {
				Node<T>* minByRight = rightChild->getMinNode();
				T value = minByRight->getValue();
				erase(minByRight);
				node->setValue(value);
				return;
			} 
			
			if (leftChild != nullptr) {
				parent->setLeftChild(leftChild);
				leftChild->setColor(Color::Black);
				delete node;
				return;
			} 
			
			if (rightChild != nullptr) {
				parent->setRightChild(rightChild);
				rightChild->setColor(Color::Black);
				delete node;
			}
		}

		Node<T>* find(T value) {
			Node<T>* currentNode = _root;
			Node<T>* parent = nullptr;

			while (currentNode != nullptr && currentNode->getValue() != value) {
				parent = currentNode;
				if (value > currentNode->getValue())
					currentNode = currentNode->getRightChild();
				else
					currentNode = currentNode->getLeftChild();
			}

			return currentNode;
		}

		T getMax() {
			return _root->getMaxNode()->getValue();
		}

		T getMin() {
			return _root->getMinNode()->getValue();
		}
	};
}
#endif