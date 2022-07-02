/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 //CARLOS FORRIOL MOLINA 
   //@ </answer>


#include <iostream>
#include <cassert>
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
		:head(copy_nodes(other.head)) { }

	void push_front(int elem) {
		Node* new_node = new Node{ elem, head };
		head = new_node;
	}

	void push_back(int elem);

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

	// Declaración del método. Impleméntalo antes de la
	// función tratar_caso()
	void intersect(const ListLinkedSingle& other);

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

void ListLinkedSingle::push_back(int elem) {
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
void ListLinkedSingle:: intersect(const ListLinkedSingle& other) {
	Node* cur = head;
	Node* ot = other.head;
	Node* prev= nullptr;
	
	while (cur != nullptr && ot != nullptr) {
		if (cur->value < ot->value) {
			if (prev != nullptr)
				prev->next = cur->next;
			else
				head = cur->next;
			cur = cur->next;
		}
		else if (cur->value > ot->value) {
			ot = ot->next;

		}
		else if(cur->value == ot->value) {
			prev = cur;
			cur = cur->next;
			ot = ot->next;
		}
		
		
	}
	if (prev != nullptr)
		prev->next = nullptr;
	else
		head = nullptr;

	delete_list(cur);
	
}

void tratar_caso() {
	int num,numElems;
	ListLinkedSingle l1,l2;
	cin >> numElems;
	for (int i = 0; i < numElems; i++) {
		cin >> num;
		l1.push_back(num);
	}
	cin >> numElems;
	for (int i = 0; i < numElems; i++) {
		cin >> num;
		l2.push_back(num);
	}
	l1.intersect(l2);
	l1.display();
	cout << endl;
	
}




int main() {
#ifndef DOMJUDGE
	std::ifstream in("1.in");
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
	// system("PAUSE");
#endif
	return 0;
}

