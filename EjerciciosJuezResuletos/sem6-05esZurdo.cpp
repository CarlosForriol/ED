#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>
#include <algorithm>
#include <string>

template <class T> class BinTree {
public:
	BinTree() : root_node(nullptr) {}

	BinTree(const T& elem)
		: root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

	BinTree(const BinTree& left, const T& elem, const BinTree& right)
		: root_node(std::make_shared<TreeNode>(left.root_node, elem,
			right.root_node)) {}

	bool empty() const { return root_node == nullptr; }

	const T& root() const {
		assert(root_node != nullptr);
		return root_node->elem;
	}

	BinTree left() const {
		assert(root_node != nullptr);
		BinTree result;
		result.root_node = root_node->left;
		return result;
	}

	BinTree right() const {
		assert(root_node != nullptr);
		BinTree result;
		result.root_node = root_node->right;
		return result;
	}

	void display(std::ostream& out) const { display_node(root_node, out); }

private:
	// Las definiciones de TreeNode y NodePointer dependen recursivamente
	// la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
	// para que el compilador sepa, cuando analice la definici�n de NodePointer,
	// que TreeNode va a ser definida m�s adelante.

	struct TreeNode;
	using NodePointer = std::shared_ptr<TreeNode>;

	struct TreeNode {
		TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
			: elem(elem), left(left), right(right) {}

		T elem;
		NodePointer left, right;
	};

	NodePointer root_node;

	static void display_node(const NodePointer& root, std::ostream& out) {
		if (root == nullptr) {
			out << ".";
		}
		else {
			out << "(";
			display_node(root->left, out);
			out << " " << root->elem << " ";
			display_node(root->right, out);
			out << ")";
		}
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
	tree.display(out);
	return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
	char c;
	in >> c;
	if (c == '.') {
		return BinTree<T>();
	}
	else {
		assert(c == '(');
		BinTree<T> left = read_tree<T>(in);
		T elem;
		in >> elem;
		BinTree<T> right = read_tree<T>(in);
		in >> c;
		assert(c == ')');
		BinTree<T> result(left, elem, right);
		return result;
	}
}

using namespace std;

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------


template<typename T>
pair<bool, int> es_zurdo_aux(const BinTree<T>& arbol) {
	if (arbol.empty())return { true,0 };
	if (arbol.left().empty() && arbol.right().empty())return{ true,1 };

	auto [eszurdoIzq, numNodosIzq] = es_zurdo_aux(arbol.left());
	auto [eszurdoDer, numNodosDer] = es_zurdo_aux(arbol.right());

	return { eszurdoIzq && eszurdoDer && numNodosIzq > numNodosDer ,1 + numNodosIzq + numNodosDer };
}

template<typename T>
bool es_zurdo(const BinTree<T> t) {
	return es_zurdo_aux(t).first;
}

// Funci�n que trata un caso de prueba
void tratar_caso() {
	BinTree<char> t = read_tree<char>(cin);
	cout << (es_zurdo(t) ? "SI" : "NO") << endl;
}


//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int numCasos;
	cin >> numCasos;

	while (numCasos--)
		tratar_caso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}