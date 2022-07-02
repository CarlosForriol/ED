/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas no será
  * corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
   * Introduce el nombre y apellidos de los/as componentes del grupo:
   *
   * Estudiante 1:
   * Estudiante 2:
   *
   */
   //@ </answer>

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

// Clase para representar árboles binarios.
// No es posible modificar esta clase para la práctica.

template <class T> class BinTree {

private:
	struct TreeNode;
	using NodePointer = std::shared_ptr<TreeNode>;

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

	template <typename U> void preorder(U func) const {
		preorder(root_node, func);
	}

	template <typename U> void inorder(U func) const { inorder(root_node, func); }

	template <typename U> void postorder(U func) const {
		postorder(root_node, func);
	}

	template <typename U> void levelorder(U func) const;

private:
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

	template <typename U> static void preorder(const NodePointer& node, U func);

	template <typename U> static void inorder(const NodePointer& node, U func);

	template <typename U> static void postorder(const NodePointer& node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
	if (node != nullptr) {
		func(node->elem);
		preorder(node->left, func);
		preorder(node->right, func);
	}
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer& node, U func) {
	if (node != nullptr) {
		inorder(node->left, func);
		func(node->elem);
		inorder(node->right, func);
	}
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
	if (node != nullptr) {
		postorder(node->left, func);
		postorder(node->right, func);
		func(node->elem);
	}
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
	std::queue<NodePointer> pending;
	if (root_node != nullptr) {
		pending.push(root_node);
	}
	while (!pending.empty()) {
		NodePointer current = pending.front();
		pending.pop();
		func(current->elem);
		if (current->left != nullptr) {
			pending.push(current->left);
		}
		if (current->right != nullptr) {
			pending.push(current->right);
		}
	}
}

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

// ----------------------------------------------------------------
//@ <answer>
//
// Implementa aquí la solución al problema.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas <answer> y </answer>

// Indica también el coste de la solución dentro de estas marcas.
BinTree<int> reconstruir1(const vector<int>& preorden,
	const vector<int>& inorden,int &pre,int &in, int tope) {
	// Completar
	if (pre == preorden.size() || inorden[in] == tope) {
		return BinTree<int>();
	}

	int raiz = preorden[pre];
	++pre;
	BinTree<int> iz = reconstruir1(preorden, inorden, pre, in, raiz);
	++in;
	BinTree<int> dr = reconstruir1(preorden, inorden, pre, in, tope);

	return BinTree<int> { iz, raiz, dr };
}

BinTree<int> reconstruir(const vector<int>& preorden,
	const vector<int>& inorden) {
	// Completar
	int pre = 0, in = 0, tope = 1;
	 return reconstruir1(preorden, inorden, pre, in, tope);
}


// Resuelve un caso de prueba, leyendo las dos listas de la entrada
// y llamando a la función reconstruir definida arriba.
bool tratar_caso() {
	// Completar
	vector<int> preorden;
	vector<int> inorden;
	BinTree<int> arbol;

	int elem,num;
	cin >> elem;
	if (elem == 0) return false;
	for (int i = 0; i < elem; i++) {
		cin >> num;
		preorden.push_back(num);

	}
	for (int j = 0; j < elem; j++) {
		cin >> num;
		inorden.push_back(num);

	}
	arbol = reconstruir(preorden, inorden);
	arbol.postorder([](int x) { std::cout << x << " "; });
	cout << endl;

	return true;
}


//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif

	return 0;
}