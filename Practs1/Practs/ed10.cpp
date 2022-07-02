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
#include <cassert>
#include <fstream>
#include <unordered_map>
#include <list>
using namespace std;

unordered_map < string, list<pair<string, string>>> leer(const int & numAlumnos, const int &pContestar, list<pair<string, bool>>& notas) {
	unordered_map < string, list<pair<string, string>>> resultado;
	
	string nombre, pregunta, respuesta;

	for (int i = 0; i < numAlumnos; i++) {

		cin >> nombre;
		
		notas.push_back({ nombre, true });

		for (int j = 0; j < pContestar; j++) {
			cin >> pregunta;
			cin >> respuesta;

			resultado.insert({ pregunta, {} });
			resultado[pregunta].push_back({ nombre, respuesta });
		}
	}
	return resultado;
}

int corregir(const unordered_map < string, list<pair<string, string>>>& examenes, const int numPreguntas, list<pair<string, bool>>& notas) {

	string pregunta, respuesta;
	
	int numDieces = 0;

	for (int i = 0; i < numPreguntas; i++) {
		cin >> pregunta >> respuesta;

		if (examenes.count(pregunta) == 1) {
			auto it = examenes.find(pregunta);
			for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++) {
				for (auto it2 = notas.begin(); it2 != notas.end(); it2++) {
					if (it2->first == it1->first && respuesta != it1->second) {
						it2->second = false;
					}
				}
			}
		}
	}
	for (auto it = notas.begin(); it != notas.end(); it++) {
		if (it->second == true) {
			numDieces++;
		}
	}
	return numDieces;

}

bool tratar_caso() {
	list<pair<string, bool>> notas;

	int numAlumnos, pContestar, numPreguntas;

	cin >> numAlumnos >> pContestar >> numPreguntas;

	if (numAlumnos == 0 && pContestar == 0 && numPreguntas == 0) return false;

	unordered_map < string,list<pair<string, string>>> examenes = leer(numAlumnos, pContestar, notas);

	cout << corregir(examenes, numPreguntas, notas) << endl;
	
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

