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

	int size() const { return size(this->root_node); }

	int altura() const { return height(this->root_node); }

	int hijos() const { return children(this->root_node); }

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

	int size(const NodePointer& root) const {//num nodos
		if (root == nullptr)return 0;
		return 1 + size(root->left) + size(root->right);
	}
	int height(const NodePointer& root) const {
		if (root == nullptr)return 0;
		return 1 + std ::max(height(root->left), height(root->right));
	}
	int children(const NodePointer& root) const {
		if (root->left == nullptr && root->right == nullptr)return 1;
		else if (root == nullptr)return 0;
		else return children(root->left) + children(root->right);

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

void tratar_caso() {
	BinTree<char> tree = read_tree<char>(cin);

	cout << tree.size() << " " << tree.hijos() << " " <<  tree.altura() << endl;
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int num_casos;
	cin >> num_casos;

	for (int i = 0; i < num_casos; i++) {
		tratar_caso();
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}