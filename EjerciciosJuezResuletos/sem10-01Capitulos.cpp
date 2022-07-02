#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;
bool tratar_caso() {
	int M;
	cin >> M;
	unordered_map<int, int> capitulos;

	int cap, max=0, noVistos=0;
	for (int i = 0; i < M; i++) {
		cin >> cap;
		if (!capitulos.count(cap)) noVistos++;
		else {
			if (i - noVistos > capitulos[cap]) {
				noVistos++;
			}
			else {
				noVistos = i - capitulos[cap];
			}
		}
		capitulos[cap] = i;
		max = std::max(max, noVistos);
	}
	cout << max << "\n";
	return true;
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int numCasos;
	cin >> numCasos;
	while (numCasos--) tratar_caso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}