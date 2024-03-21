#pragma once

#include <iostream>
#include <stdexcept>
#include <random>
#include <functional>

using namespace std;

namespace trees {
	template<typename T>
	struct Node {
		T val;
		Node<T>* left;
		Node<T>* right;

		Node() : val(0), left(nullptr), right(nullptr) {}
		Node(T v) : val(v), left(nullptr), right(nullptr) {}
	};

	template<typename T>
	class Set {
	private:
		Node<T>* _root;

		Node<T>* copy(Node<T>* node) {
			if (node) {
				Node<T>* new_node = new Node<T>(node->val);
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
				if (!node->left || !node->right) {
					Node<T>* tmp = node;
					node = (node->left) ? node->left : node->right;
					delete tmp;
				}
				else {
					Node<T>* tmp = node->right;
					while (tmp->left) tmp = tmp->left;
					node->val = tmp->val;
					erase(node->right, tmp->val);
				}
				return true;
			}
		}

	public:
		Set() : _root(nullptr) {}

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

	int random(int a, int b) {
		random_device random_device;
		mt19937 generator(random_device());
		uniform_int_distribution<> segment(a, b);
		int x = segment(generator);
		return x;
	}

	int random_seed(int a, int b, int seed) {
		mt19937 generator(seed);
		uniform_int_distribution<> segment(a, b);
		int x = segment(generator);
		return x;
	}

	template<typename T>
	void add_new_items(Set<T>& set, Node<T>* node) {
		if (node) {
			add_new_items(set, node->left);
			if (!(set.contains(node->val))) set.insert(node->val);
			add_new_items(set, node->right);
		}
	}

	template<typename T>
	Set<T> union_set(Set<T>& set1, Set<T>& set2) {
		Set<T> set(set1);
		add_new_items(set, set2.get_root());
		return set;
	}

	template<typename T>
	void delete_identical_items(Set<T>& set, Node<T>* node) {
		if (node) {
			delete_identical_items(set, node->left);
			if (set.contains(node->val)) set.erase(node->val);
			delete_identical_items(set, node->right);
		}
	}

	template<typename T>
	Set<T> difference_set(Set<T>& set1, Set<T>& set2) {
		Set<T> set(set1);
		delete_identical_items(set, set2.get_root());
		return set;
	}

	template<typename T>
	Set<T> intersec_set(Set<T>& set1, Set<T>& set2) {
		Set<T> res = difference_set(set1, set2);
		return difference_set(set1, res);
	}
}