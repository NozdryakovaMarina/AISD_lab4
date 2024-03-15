#pragma once

#include <iostream>
#include <stdexcept>
#include <random>

using namespace std;

namespace trees {
	template<typename T>
	struct Node { 
		T val;
		Node<T>* left;
		Node<T>* right;

		Node(): val(0), left(nullptr), right(nullptr) {}
		Node(T v): val(v), left(nullptr), right(nullptr) {}
	};

	template<typename T>
	class Set {
	private:
		Node<T>* _root; 

		Node<T>* copy(Node<T>* node) {
			if (node) {
				Node<T>* new_node = new Node<T>(node->data);
				new_node->left = copy(node->left);
				new_node->right = copy(node->right);
				return new_node;
			}
			return nullptr;
		}

		void clear(Node<T>* cur) {
			if (!cur) return;

			clear(cur->left);
			clear(cur->right);
			delete cur;
		}

		void print(Node<T>* cur) {
			if (cur) {
				print(cur->left);
				cout << cur->val << " ";
				print(cur->right);
			}
		}

		bool insert(Node<T>*& node, T key) {
			if (!node) {
				node = new Node<T>(key);
				return true;
			}
			if (node->val > key) {
				return insert(node->left, key);
			}
			else if (node->val < key) {
				return insert(node->right, key);
			}
			return false;
		}

		bool contains(Node<T>* node, T key) {
			if (!node) return false;

			if (node->val > key) return contains(node->left, key);

			else if (node->val < key) return contains(node->right, key);

			return true;
		}

		bool erase(Node<T>*& node, T key) {
			if (!node) return false;

			if (node->val > key) return erase(node->left, key);

			else if (node->val < key) return erase(node->right, key);
			else {
				if (!node->left) {
					Node<T>* tmp = node->left;
					delete node;
					node = tmp;
				}
				else if (!node->right) {
					Node<T>* tmp = node->right;
					delete node;
					node = tmp;
				}
				else {
					Node<T>* tmp = node->right;
					while (tmp->left) {
						tmp = tmp->left;
					}
					node->val = tmp->val;
					erase(node->right, tmp->val);
				}
				return true;
			}
		}

	public:
		Set(): _root(nullptr){}

		Set(const Set<T>& other) {
			_root = copy(other._root);
		}

		~Set() {
			clear(_root);
		}

		Set<T>& operator = (Set<T> other) {
			swap(_root, other._root);
			return *this;
		}

		Node<T>* get_root() const {
			return _root;
		}

		void print() {
			print(_root);
			cout << endl;
		}

		bool insert(T key) {
			return insert(_root, key);
		}

		bool contains(T key) {
			return contains(_root, key);
		}

		bool erase(T key) {
			return erase(_root, key);
		}
	};
  };