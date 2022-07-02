/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Introduce el nombre y apellidos de los/as componentes del grupo:
  *
  * Estudiante 1:Javier de Hoyos Pino
  * Estudiante 2:Carlos Forriol Molina
  *
  */

#include <iostream>
#include <fstream>
#include <string>
#include<stack>
#include <unordered_map>
#include <algorithm>
#include<vector>
#include <list>
using namespace std;

class AcademiaChino {
public:
	// Definiciones públicas ¡No olvides el coste!

	AcademiaChino() {
		vector<list<string>> aux(8);

		academia = aux;
	}

	void nuevo_estudiante(const string& dni, const int& grupo) { //coste : O(1)

		if (estudiantes.count(dni)) {
			throw std::domain_error("ERROR: Estudiante existente");
		}

		if (grupo < 1 || grupo > 6) {
			throw std::domain_error("ERROR: Grupo incorrecto");
		}

		academia[grupo].push_front( dni );
		estudiantes[dni] = { grupo, academia[grupo].begin()};
	}

	void promocianar(const string& dni) {//coste : O(1)

		info_estudiante &grupo = buscar_alumno(dni);

		if (grupo.grupo == 7) {
			throw std::domain_error("ERROR: Estudiante ya graduado");
		}
		
		list<string>& aux = academia[grupo.grupo];

		grupo.grupo++;

		aux.erase(grupo.it_cola);

		academia[grupo.grupo].push_front(dni);

		grupo.it_cola = academia[grupo.grupo].begin();

	}

	int grupo_estudiante(const string& dni) { //coste : O(1)

		int grupo = buscar_alumno(dni).grupo;

		if (grupo == 7) {
			throw std::domain_error("ERROR: Estudiante ya graduado");
		}
		return grupo;
	}

	string novato(const int& grupo) {//coste : O(1)

		if (grupo < 1 || grupo > 6) {
			throw std::domain_error("ERROR: Grupo incorrecto");
		}

		if (academia[grupo].empty()) {
			throw std::domain_error("ERROR: Grupo vacio");
		}

		return academia[grupo].front();
	}

	 list <string> graduados() {//coste : O(nlog(n)) siendo n el numero de graduados
		
			academia[7].sort();
			return academia[7];
	}

private:
	// Definiciones privadas

	struct info_estudiante {
		int grupo;
		list<string>::iterator it_cola;
		info_estudiante(){ }
		info_estudiante(int grupo, list<string>::iterator it) : grupo(grupo), it_cola(it){ }
	};
	int grupos;
	unordered_map<string, info_estudiante> estudiantes;
	
	vector<list<string>> academia;

	info_estudiante& buscar_alumno(const string& dni) {
		auto it = estudiantes.find(dni);
		if (it == estudiantes.end()) {
			throw std::domain_error("ERROR: Estudiante no existente");
		}
		else {
			return it->second;
		}
	}
	const info_estudiante& buscar_alumno(const string& dni) const {
		auto it = estudiantes.find(dni);
		if (it == estudiantes.end()) {
			throw std::domain_error("ERROR: Estudiante no existente");
		}
		else {
			return it->second;
		}
	}
};

bool tratar_caso() {
	// Implementar
	AcademiaChino ac;
	string funcion, dni;
	int grupo;

	cin >> funcion;

	if (cin.eof()) {
		return false;
	}

	while (funcion != "FIN") {
		try {
			if (funcion == "nuevo_estudiante") {
				cin >> dni;
				cin >> grupo;

				ac.nuevo_estudiante(dni, grupo);
			}

			if (funcion == "promocionar") {
				cin >> dni;

				ac.promocianar(dni);
			}

			if (funcion == "grupo_estudiante") {
				cin >> dni;

				grupo = ac.grupo_estudiante(dni);

				cout << dni << " esta en el grupo " << grupo << endl;
 			}

			if (funcion == "novato") {
				cin >> grupo;

				dni = ac.novato(grupo);

				cout << "Novato de " << grupo << ": " << dni << endl;
			}

			if (funcion == "graduados") {
				 list <string> g = ac.graduados();
				cout << "Lista de graduados: ";
				for (auto it = g.begin(); it != g.end(); it++) {
					cout << *it << " ";
				}
				cout << endl;
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		cin >> funcion;
	}

	cout << "---" << endl;
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
	 system("PAUSE");
#endif
	return 0;
}
