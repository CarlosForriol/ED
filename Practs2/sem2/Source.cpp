/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
	Introduce aquí los nombres de los componentes del grupo:

	Componente 1:Carlos Forriol Molina
	Componente 2:Daniel Garcia Arroyo
  */
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
		: head(copy_nodes(other.head)) { }

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
	void escamochar(ListLinkedSingle& dest);

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

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------


// ¡No olvides indicar el coste del método!
//Coste O(N) siendo N numero de elementos de this
void ListLinkedSingle::escamochar(ListLinkedSingle& dest) {
	
	Node* cur = head;
	Node* temp = nullptr;
	Node* destcur = nullptr;
	//Transporta los primeros negativos(si hay)
	while (cur != nullptr && cur->value < 0) {
		temp = cur;
		cur = cur->next;
		if (!dest.empty()) {
			destcur->next = temp;
			destcur = destcur->next;
		}
		else {
			dest.head = temp;
			destcur = dest.head;
		}
	}
	if(!dest.empty())destcur->next = nullptr;//next ultelem dest = NULL(destcur acaba apuntando final dest)
	head = cur;//eliminar de this

	Node* ultPos = nullptr;
	while (cur != nullptr) {//Busca ultimo Positivo this
		if (cur->value >= 0) {
			ultPos = cur;
		}
		cur = cur->next;
	}
	//Transporta los ultimos negativos(si hay)
	if (ultPos != nullptr) {
		cur = ultPos;
		ultPos = ultPos->next;
	   while (ultPos != nullptr) {
		  if (!dest.empty()) {
			destcur->next = ultPos;
			destcur = destcur->next;
		  }
		  else {
			dest.head = ultPos;
			destcur = dest.head;
		  }
		  //Enganchar en this
		  temp = ultPos->next;
		  ultPos = temp;
		  cur->next = temp;
	 }
	   if (!dest.empty())destcur->next = nullptr;
	}	
	
}
	
void tratar_caso() {
	// Introduce aquí el código para tratar un caso de prueba.
	// Devuelve false si se ha leído la marca de fin de entrada;
	// true en caso contrario.
	ListLinkedSingle l1,l2;
	int numElems, elems;
	cin >> numElems;
	for (int i = 0; i <numElems; i++) {
		cin >> elems;
		l1.push_front(elems);
	}
	if(numElems!=0)l1.escamochar(l2);
	l1.display();
	cout << endl;
	l2.display();
	cout << endl;

}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
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