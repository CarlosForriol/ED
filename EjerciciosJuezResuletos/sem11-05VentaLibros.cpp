#include <iostream>
#include <fstream>
#include <string> 
#include <list>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>

using namespace std;

class VentaLibros {
public:

	void nuevoLibro(int ejemplares, const string& libro) {
		if (libros.count(libro))libros[libro].ejemplares += ejemplares;
		else {
			libros[libro] = {ejemplares,0};
			 
		}

	}

	void comprar(const string& libro) {
		InfoLibro& info = buscar_libro(libro);
		
		info.ejemplares--;
		info.vendidos++;
		if(!ventas.count({ info.vendidos-1 ,libro }))ventas.insert({ info.vendidos ,libro });
		
	}

	bool estaLibro(const string& libro) const {
		return libros.count(libro);
	}

	void elimLibro(const string& libro) {
		if (libros.count(libro)) {
			libros.erase(libro);
			InfoLibro& info = buscar_libro(libro);
			ventas.erase({ info.vendidos ,libro });
		}
	}

	int numEjemplares(const string& libro) const {
		if (!libros.count(libro))throw invalid_argument("Libro no existente");
		return libros.at(libro).ejemplares;
	}

	list<string> top10() {
		list<string> lista;
		set<pair<int,string>>::iterator it = ventas.begin();
		int i = 0;
		while (it != ventas.end() && i < 9){
			lista.push_back(it->second);
			
			it++;
			i++;
		}
		return lista;
	}

private:

	struct InfoLibro {
		int ejemplares;
		int vendidos;
	};
	unordered_map<string, InfoLibro> libros;
	set<pair<int, string>> ventas;
	
	InfoLibro& buscar_libro(const string& libro) {
		auto it = libros.find(libro);
		if (it == libros.end()) throw invalid_argument("Libro no existente");
		if (it->second.ejemplares == 0) throw out_of_range("No hay ejemplares");

		return it->second;
	}
	const InfoLibro& buscar_libro(const string& libro) const {
		auto it = libros.find(libro);
		if (it == libros.end()) throw invalid_argument("Libro no existente");
		if (it->second.ejemplares == 0) throw out_of_range("No hay ejemplares");

		return it->second;
	}

};

bool tratar_caso() {
	int N;
	cin >> N;
	if (!cin) return false;

	VentaLibros venta;
	string opcion, libro;
	int ejemplares;
	while (N--) {
		cin >> opcion;
		try {
			if (opcion == "nuevoLibro") {
				cin >> ejemplares;
				getline(cin, libro);

				venta.nuevoLibro(ejemplares, libro);
			}
			else if (opcion == "comprar") {
				getline(cin, libro);
				venta.comprar(libro);
			}
			else if (opcion == "estaLibro") {
				getline(cin, libro);
				if (venta.estaLibro(libro))
					cout << "El libro " << libro << " esta en el sistema\n";
				else
					cout << "No existe el libro " << libro << "en el sistema \n";
			}
			else if (opcion == "elimLibro") {
				getline(cin, libro);
				venta.elimLibro(libro);
			}
			else if (opcion == "numEjemplares") {
				getline(cin, libro);
				int numEjemplares = venta.numEjemplares(libro);

				if (numEjemplares == -1)
					cout << "No existe el libro x en el sistema\n";
				else
					cout << "Existen " << numEjemplares << " ejemplares del libro " << libro << "\n";
			}
			else if (opcion == "top10") {
				cout << "TOP 10\n";
				list<string> top = venta.top10();
				
				for (auto elem : top) cout << "\t " << elem << "\n";
			}
		}
		catch (invalid_argument& argument) {
			cout << argument.what() << "\n";
		}
		catch (out_of_range& exception) {
			cout << exception.what() << "\n";
		}
	}

	cout << "---\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.txt");
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