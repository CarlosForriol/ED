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
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
using namespace std;

class ConteoVotos {
public:
	void nuevo_estado(const string& nombre, int num_compromisarios) {//coste: O(1)

		auto it = sistema.find(nombre);

		if (it == sistema.end()) {
			sistema.insert({ nombre, {num_compromisarios, {}}});
		}
		else{
			throw std::domain_error("Estado ya existente");
		}

	}

	void sumar_votos(const string& estado, const string& partido, int num_votos) {//coste: O(1)

		InfoEstado& info = buscar_estado(estado);

		int maxVotos = info.partido[partido] += num_votos;

		if (info.partido[partido] > info.ganador.second) {
			if (resultado.count(info.ganador.first) == 1) {

				resultado.at(info.ganador.first) -= info.compromisarios;

				if (resultado.at(info.ganador.first) == 0) {
					resultado.erase(info.ganador.first);
				}
			}
			info.ganador.first = partido;
			info.ganador.second = maxVotos;
			
			resultado[partido] += info.compromisarios;
		}
		
	}

	string ganador_en(const string& estado) const {//coste: O(1)
		const InfoEstado& info = buscar_estado(estado);
		
		return info.ganador.first;
	}

	vector<pair<string, int>> resultados() const {//coste: O(n) siendo n el numero de partidos
		vector<pair<string, int>> result;
		
		for (auto it = resultado.begin(); it != resultado.end(); it++) {

			result.push_back({it->first, it->second});
		}
		return result;
	}

private:
	
	
	struct InfoEstado {
		int compromisarios;
		map<string, int> partido;//partidos, votos
		pair<string, int> ganador;//partido, votos
	};


	unordered_map<string, InfoEstado> sistema;//estado, InfoEstado

	map<string, int> resultado;//partidos, num_compromisarios

	InfoEstado& buscar_estado(const string& estado) {
		auto it = sistema.find(estado);
 		if (it == sistema.end()) {
			throw std::domain_error("Estado no encontrado");
		}
		else {
			return it->second;
		}
	}

	const InfoEstado& buscar_estado(const string& estado) const{
	auto it = sistema.find(estado);
		if (it == sistema.end()) {
			throw std::domain_error("Estado no encontrado");
		}
		else {
			return it->second;
		}
	}

};


bool tratar_caso() {

	ConteoVotos conteo;
	string funcion, estado, partido;
	int votos, compromisarios;

	cin >> funcion;

	if (cin.eof()) {
		return false;
	}

	while (funcion != "FIN") {
		try {
			if (funcion == "nuevo_estado") {
				cin >> estado;
				cin >> compromisarios;

				conteo.nuevo_estado(estado, compromisarios);
			}

			if (funcion == "sumar_votos") {
				cin >> estado;
				cin >> partido;
				cin >> votos;

				conteo.sumar_votos(estado, partido, votos);
			}

			if (funcion == "ganador_en") {
				cin >> estado;

				string ganador = conteo.ganador_en(estado);
				cout << "Ganador en " << estado << ": " << ganador << "\n";

			}

			if (funcion == "resultados") {
				vector<pair<string, int>> v = conteo.resultados();

				for (int i = 0; i < v.size(); i++) {
					cout << v[i].first << " " << v[i].second << endl;
				}
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
	// system("PAUSE");
#endif
	return 0;
}
