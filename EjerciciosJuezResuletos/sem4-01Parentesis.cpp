#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>

using namespace std;

// Puedes copiar aquí algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED/blob/main/lineales/stack_linkedlist/stack_linkedlist.h
// Colas: https://github.com/manuelmontenegro/ED/blob/main/lineales/queue_linkedlist/queue_linkedlist.h
// Colas dobles: https://github.com/manuelmontenegro/ED/blob/main/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ningún cambio
// en sus implementaciones. Para facilitar la corrección, coloca la implementación de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumirá que tienen la misma implementación que la
// vista en teoría.

// Alternativamente, puedes utilizar las clases de la librería estándar de C++ (stack<T>, queue<T> y deque<T>).

/*
 * Implementación del TAD Cola mediante listas enlazadas.
 */
 /*
  * ---------------------------------------------------
  *                ESTRUCTURAS DE DATOS
  * ---------------------------------------------------
  *              Manuel Montenegro Montes
  *              Facultad de Informática
  *         Universidad Complutense de Madrid
  * ---------------------------------------------------
  */

  /*
   * Implementación del TAD Pila mediante listas enlazadas simples.
   */

#ifndef __STACK_LINKEDLIST_H
#define __STACK_LINKEDLIST_H

#include <cassert>
#include <iostream>
#include <iostream>
#include <string>

template <typename T> class StackLinkedList {
public:
	StackLinkedList() : top_node(nullptr) {}
	StackLinkedList(const StackLinkedList& other)
		: top_node(copy_nodes_from(other.top_node)) {}

	~StackLinkedList() { free_nodes_from(top_node); }

	StackLinkedList& operator=(const StackLinkedList& other) {
		if (this != &other) {
			free_nodes_from(top_node);
			top_node = copy_nodes_from(other.top_node);
		}
		return *this;
	}

	void push(const T& elem) { top_node = new Node{ elem, top_node }; }

	void pop() {
		assert(top_node != nullptr);
		Node* target = top_node;
		top_node = top_node->next;
		delete target;
	}

	T& top() {
		assert(top_node != nullptr);
		return top_node->value;
	}

	const T& top() const {
		assert(top_node != nullptr);
		return top_node->value;
	}

	bool empty() const { return (top_node == nullptr); }

private:
	struct Node {
		T value;
		Node* next;
	};

	Node* copy_nodes_from(Node* other);
	void free_nodes_from(Node* other);

	Node* top_node;
};

template <typename T>
typename StackLinkedList<T>::Node*
StackLinkedList<T>::copy_nodes_from(Node* other) {
	if (other == nullptr) {
		return nullptr;
	}
	else {
		Node* first = new Node{ other->value, nullptr };
		Node* last = first;
		Node* current = other->next;
		while (current != nullptr) {
			Node* new_node = new Node{ current->value, nullptr };
			last->next = new_node;
			current = current->next;
			last = new_node;
		}
		return first;
	}
}

template <typename T> void StackLinkedList<T>::free_nodes_from(Node* other) {
	Node* current = other;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

#endif

bool tratar_caso() {
	StackLinkedList<char> pila;
	string cadena;
	getline(cin, cadena);
	bool equilibrado = true;
	if (!cin)return false;

	for (int i = 0; i < cadena.size() && equilibrado; i++) {
		if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[')
			pila.push(cadena[i]);
		if (cadena[i] == ')') {
			if (!pila.empty() && pila.top() == '(' )pila.pop();
			else equilibrado = false;
		}
		if (cadena[i] == ']') {
			if (!pila.empty() && pila.top() == '['  )pila.pop();
			else equilibrado = false;
		}
		if (cadena[i] == '}') {
			if (!pila.empty() && pila.top() == '{')pila.pop();
			else equilibrado = false;
		}
	}
	if (!pila.empty())
		equilibrado = false;
	if (equilibrado)
		cout << "SI\n";
	else
		cout << "NO\n";
	return true;

}
int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}