/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas no será
  * corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
   * Introduce el nombre y apellidos de los/as componentes del grupo:
   *
   * Estudiante 1:javier de hoyos pino
   * Estudiante 2:carlos forriol molina
   *
   */
   //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <queue>

using namespace std;



// Puedes copiar aquí algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED-2021/blob/master/lineales/stack_array/stack_array.h
// Colas: https://github.com/manuelmontenegro/ED-2021/blob/master/lineales/queue_array/queue_array.h
// Colas dobles: https://github.com/manuelmontenegro/ED-2021/blob/master/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ningún cambio
// en sus implementaciones. Para facilitar la corrección, coloca la implementación de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumirá que tienen la misma implementación que la
// vista en teoría.

// Alternativamente, puedes utilizar las clases de la librería estándar de C++ (stack<T>, queue<T> y deque<T>).

#ifndef __STACK_ARRAY_H
#define __STACK_ARRAY_H

#include <cassert>
#include <iostream>

const int DEFAULT_CAPACITY = 10;

template <typename T> class StackArray {
public:
	StackArray(int initial_capacity = DEFAULT_CAPACITY)
		: num_elems(0), capacity(initial_capacity), elems(new T[capacity]) {}

	~StackArray() { delete[] elems; }

	void push(const T& elem) {
		if (num_elems == capacity) {
			resize_array(capacity * 2);
		}

		elems[num_elems] = elem;
		num_elems++;
	}

	void pop() {
		assert(num_elems > 0);
		num_elems--;
	}

	const T& top() const {
		assert(num_elems > 0);
		return elems[num_elems - 1];
	}

	T& top() {
		assert(num_elems > 0);
		return elems[num_elems - 1];
	}

	bool empty() const { return num_elems == 0; }

private:
	int num_elems;
	int capacity;
	T* elems;

	void resize_array(int new_capacity);
};

template <typename T> void StackArray<T>::resize_array(int new_capacity) {
	T* new_elems = new T[new_capacity];

	for (int i = 0; i < num_elems; i++) {
		new_elems[i] = elems[i];
	}

	delete[] elems;
	elems = new_elems;
	capacity = new_capacity;
}

#endif
// ----------------------------------------------------------------
//@ <answer>

bool comprobar(int elem, StackArray<int>& p) {
	while (!p.empty()) {
		if (elem < p.top()) {
			return true;
		}
		else {
			p.pop();
		}
	}

	return false;
}

bool tratar_caso() {//se implementa mediante el TAD cola + TAD pila
	// Completar
	queue <int> c;
	StackArray<int> p;
	int aux;
	int ultimo = -1;

	cin >> aux;

	if (aux == -1)return false;

	while (aux != -1) {
		c.push(aux);
		cin >> aux;
	}

	

	int ant = -1;

	while (!c.empty()) {

		if (ant <= c.front()) {

			if (comprobar(c.front(), p)) {
				cout << p.top() << endl;
				p.push(ultimo);
			}
			else {
				cout << "NO HAY" << endl;
			}
		}
		else {
			cout << ant << endl;

			ultimo = ant;
			p.push(ant);
		}

		ant = c.front();
		c.pop();
	}

	cout << "---" << endl;

	return true;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}