/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>
#include <algorithm>

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
template < typename T >
T minimo(const BinTree<T>& tree) {
	T valor = tree.root();
	if (tree.left().empty() && tree.right().empty())return tree.root();
	if (!tree.left().empty()) {
		T minIzq = minimo(tree.left());
		valor = std::min(valor, minIzq);
	}
	if (!tree.right().empty()) {
		T minDer = minimo(tree.right());
		valor = std::min(valor, minDer);
	}
	return valor;
}


bool tratar_caso() {
	char caso;
	cin >> caso;
	if(!cin)return false;
	if (caso == 'N') {
		BinTree<int> tree = read_tree<int>(cin);
		cout << minimo(tree) << endl;
	}
	if (caso == 'P') {
		BinTree<string> tree = read_tree<string>(cin);
		cout << minimo(tree) << endl;
	}


	return true;
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (tratar_caso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}