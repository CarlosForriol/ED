/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*
  * Introduce el nombre y apellidos de los/as componentes del grupo:
  *
  * Estudiante 1: Carlos Forriol Molina
  * Estudiante 2: Javier de Hoyos Pino
  *
  */

#include <iostream>
#include <fstream>
#include <list>


using namespace std;


bool es_toeplitz(const list<list<int>>& matriz) {
	// Implementar
	list<list<int>> ::iterator it, it2;
	for (auto it = matriz.begin(); it != matriz.end(); it++) {
		if (it == it2++) {
			return true;
			it++;
			it2++;
		}
	}
	return true;
}


bool tratar_caso() {
	// Implementar
	list<list<int>> matriz;
	list<int> Laux;

	int n,i;
	cin >> n;
	while (n != 0) {
		while (n != 0) {
			Laux.push_back(n);
		}
		matriz.push_back(Laux);
		cin >> n;
	}
	bool ok = es_toeplitz(matriz);
	if (ok) {
		cout << "SI" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
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