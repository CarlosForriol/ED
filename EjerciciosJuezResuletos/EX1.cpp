#include <cassert>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node* next;
	};

public:
	ListLinkedSingle() : head(nullptr) { }
	~ListLinkedSingle() {
		delete_list(head);
	}

	ListLinkedSingle(const ListLinkedSingle& other)
		: head(copy_nodes(other.head)) { }

	void push_front(const int& elem) {
		Node* new_node = new Node{ elem, head };
		head = new_node;
	}

	void push_back(const int& elem);

	void pop_front() {
		assert(head != nullptr);
		Node* old_head = head;
		head = head->next;
		delete old_head;
	}

	void pop_back();

	int size() const;

	bool empty() const {
		return head == nullptr;
	};

	const int& front() const {
		assert(head != nullptr);
		return head->value;
	}

	int& front() {
		assert(head != nullptr);
		return head->value;
	}

	const int& back() const {
		return last_node()->value;
	}

	int& back() {
		return last_node()->value;
	}

	const int& at(int index) const {
		Node* result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	int& at(int index) {
		Node* result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	void display(std::ostream& out) const;
	void display() const {
		display(std::cout);
	}

	//void reverseSegment(int init, int fin);

	void unzip(ListLinkedSingle& dest);

private:
	Node* head;

	void delete_list(Node* start_node);
	Node* last_node() const;
	Node* nth_node(int n) const;
	Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
	if (start_node != nullptr) {
		Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
		return result;
	}
	else {
		return nullptr;
	}
}

void ListLinkedSingle::delete_list(Node* start_node) {
	if (start_node != nullptr) {
		delete_list(start_node->next);
		delete start_node;
	}
}

void ListLinkedSingle::push_back(const int& elem) {
	Node* new_node = new Node{ elem, nullptr };
	if (head == nullptr) {
		head = new_node;
	}
	else {
		last_node()->next = new_node;
	}
}

void ListLinkedSingle::pop_back() {
	assert(head != nullptr);
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		Node* previous = head;
		Node* current = head->next;

		while (current->next != nullptr) {
			previous = current;
			current = current->next;
		}

		delete current;
		previous->next = nullptr;
	}
}

int ListLinkedSingle::size() const {
	int num_nodes = 0;

	Node* current = head;
	while (current != nullptr) {
		num_nodes++;
		current = current->next;
	}

	return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
	assert(head != nullptr);
	Node* current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
	assert(0 <= n);
	int current_index = 0;
	Node* current = head;

	while (current_index < n && current != nullptr) {
		current_index++;
		current = current->next;
	}

	return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
	out << "[";
	if (head != nullptr) {
		out << head->value;
		Node* current = head->next;
		while (current != nullptr) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}
void ListLinkedSingle::unzip(ListLinkedSingle& dest) {
	Node* curr = head->next;
	Node* prevCurr = head;
	int i = 1; 
	while (curr != nullptr) {
		if (i % 2 == 1) {
			Node* tmp = curr;
			prevCurr->next = curr->next;
			curr = curr->next;
			dest.push_back(tmp->value);
		}
		else {
			curr = curr->next;
			prevCurr = prevCurr->next;
		}
		i++;
	}
}

void tratar_caso() {
	ListLinkedSingle l1, l2;
	int N, M, num;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		l1.push_back(num);
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> num;
		l2.push_back(num);
	}
	l1.unzip(l2);
	l1.display();
	cout << endl;
	l2.display();
	cout << endl;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int num_casos;
	cin >> num_casos;
	for (int i = 0; i < num_casos; i++) {
		tratar_caso();
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	system("PAUSE");
#endif
	return 0;
}