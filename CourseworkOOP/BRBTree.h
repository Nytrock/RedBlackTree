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
		template<T> Node(T value, Node<T>* parent) {
			_value = value;
			_leftChild = nullptr;
			_rightChild = nullptr;
			_parent = parent;
			_color = Color::Red;
		}

		void changeColor(Color color) {

		}

		T getValue() {

		}

		Color getColor() {

		}

		Node<T>* getLeftChild() {

		}

		Node<T>* getRightChild() {

		}

		Node<T>* getParent() {

		}

		void takePlaceOfParent() {

		}
	};

	template <typename T> class BRBTree {
	private:
		Node<T>* _root;
		void balanceTreeAfterInsert() {

		}
		void balanceTreeAfterErase() {

		}

		T getMax(Node<T>* node) {

		}

		T getMin(Node<T>* node) {

		}
	public:
		void insert(T value) {

		}

		void erase(T value) {

		}

		void erase(Node<T>* node) {

		}

		T getMax() {

		}

		T getMin() {

		}

		Node<T>* find(T value) {

		}
	};
}
#endif