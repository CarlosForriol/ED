#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
	struct Node {
		int value;
		Node* next;
		Node* prev;
	};

public:
	ListLinkedDouble() : num_elems(0) {
		head = new Node;
		head->next = head;
		head->prev = head;
	}

	ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
		copy_nodes_from(other);
		num_elems = other.num_elems;
	}

	~ListLinkedDouble() { delete_nodes(); }

	void push_front(const int& elem) {
		Node* new_node = new Node{ elem, head->next, head };
		head->next->prev = new_node;
		head->next = new_node;
		num_elems++;
	}

	void push_back(const int& elem) {
		Node* new_node = new Node{ elem, head, head->prev };
		head->prev->next = new_node;
		head->prev = new_node;
		num_elems++;
	}

	void pop_front() {
		assert(num_elems > 0);
		Node* target = head->next;
		head->next = target->next;
		target->next->prev = head;
		delete target;
		num_elems--;
	}

	void pop_back() {
		assert(num_elems > 0);
		Node* target = head->prev;
		target->prev->next = head;
		head->prev = target->prev;
		delete target;
		num_elems--;
	}

	int size() const { return num_elems; }

	bool empty() const { return num_elems == 0; };

	const int& front() const {
		assert(num_elems > 0);
		return head->next->value;
	}

	int& front() {
		assert(num_elems > 0);
		return head->next->value;
	}

	const int& back() const {
		assert(num_elems > 0);
		return head->prev->value;
	}

	int& back() {
		assert(num_elems > 0);
		return head->prev->value;
	}

	const int& operator[](int index) const {
		assert(0 <= index && index < num_elems);
		Node* result_node = nth_node(index);
		return result_node->value;
	}

	int& operator[](int index) {
		assert(0 <= index && index < num_elems);
		Node* result_node = nth_node(index);
		return result_node->value;
	}

	ListLinkedDouble& operator=(const ListLinkedDouble& other) {
		if (this != &other) {
			delete_nodes();
			head = new Node;
			head->next = head->prev = head;
			copy_nodes_from(other);
			num_elems = other.num_elems;
		}
		return *this;
	}

	void display(std::ostream& out) const;

	void display() const { display(std::cout); }


	// Nuevo m�todo
	// Se implementa m�s abajo
	void zip(ListLinkedDouble& other);


private:
	Node* head;
	int num_elems;

	Node* nth_node(int n) const;
	void delete_nodes();
	void copy_nodes_from(const ListLinkedDouble& other);

	// Nuevos m�todos
	// Se implementan m�s abajo
	static void attach(Node* node, Node* before);
	static void detach(Node* node);
};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
	int current_index = 0;
	Node* current = head->next;

	while (current_index < n && current != head) {
		current_index++;
		current = current->next;
	}

	return current;
}

void ListLinkedDouble::delete_nodes() {
	Node* current = head->next;
	while (current != head) {
		Node* target = current;
		current = current->next;
		delete target;
	}

	delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
	Node* current_other = other.head->next;
	Node* last = head;

	while (current_other != other.head) {
		Node* new_node = new Node{ current_other->value, head, last };
		last->next = new_node;
		last = new_node;
		current_other = current_other->next;
	}
	head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
	out << "[";
	if (head->next != head) {
		out << head->next->value;
		Node* current = head->next->next;
		while (current != head) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
	l.display(out);
	return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------

// No olvides el coste!
// Coste constante
void ListLinkedDouble::attach(Node* node, Node* before) {
	before->prev->next = node;
	before->prev = node;
	node->next = before;
	node->prev = before->prev;
}

// No olvides el coste!
// Coste constante
void ListLinkedDouble::detach(Node* node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

// No olvides el coste!
// Coste O(N) con respecto al n�mero de elementos que tiene la lista
void ListLinkedDouble::zip(ListLinkedDouble& other) {
	Node* curr = head->next;
	Node* otherCurr = other.head->next;

	while (curr != head && otherCurr != other.head) {
		Node* tmpOther = otherCurr->next;
		Node* tmpThis = curr->next;
		detach(otherCurr);
		attach(otherCurr, curr->next);
		curr = tmpThis;
		otherCurr = tmpOther;
	}
	while (otherCurr != other.head) {
		Node* tmpOther = otherCurr->next;
		detach(otherCurr);
		attach(otherCurr, head);
		otherCurr = tmpOther;
	}
	num_elems += other.num_elems;

}

//}}}  

void  tratar_caso() {
	int N, value;
	ListLinkedDouble list;
	cin >> N;

	while (N--) {
		cin >> value;
		list.push_back(value);
	}

	ListLinkedDouble other;
	cin >> N;

	while (N--) {
		cin >> value;
		other.push_back(value);
	}

	list.zip(other);
	cout << list << endl;
}

//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++)
		tratar_caso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}