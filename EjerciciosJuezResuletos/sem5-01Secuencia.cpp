
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
bool tratar_caso() {
	string linea;
	getline(cin, linea);
	if (!cin)return false; 
	stringstream flujo(linea);
	string secuencia;
	
	
	auto it = secuencia.begin();

	char tecla;
	while (flujo >> tecla) {
		if (tecla == '-')it = secuencia.begin();
		else if (tecla == '+')it = secuencia.end();
		else if (tecla == '*')it++;
		else if (tecla == '3')it = secuencia.erase(it);
		else {
			secuencia.insert(it, tecla);
			it++;
		}
	}
	cout << secuencia << endl;
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