/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Introduce el nombre y apellidos de los/as componentes del grupo:
  *
  * Estudiante 1:Carlos Forriol Molina
  * Estudiante 2: Javier de Hoyos Pino
  *
  */

#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;
/ Define la clase 'Polinomio' aquí /

const int MAX_MONOMIOS = 10000;
class Polinomio {
public:
	Polinomio() {

		num_monomios = 0;

	};

	int evaluar(int v) const;

	void anyadir_monomio(int coef, int exp)
	{
		int pos = 0;

		if (coef != 0)
		{

			if (exponenteReptido(exp, 0, num_monomios, pos))
			{
				expIguales(coef, pos);
			}
			else
			{
				AnyadirConOrden(coef, exp);

				num_monomios++;
			}
		}
	}

	bool exponenteReptido(int exp, int ini, int fin, int& pos);

	void AnyadirConOrden(int coef, int exp);

	void expIguales(int coef, int pos)
	{
		this->monomios[pos].coeficiente += coef;
	}

private:
	struct Monomio {
		int coeficiente;
		int exponente;
	};
	Monomio monomios[MAX_MONOMIOS];
	int num_monomios;
};

bool Polinomio::exponenteReptido(int exp, int inicio, int fin, int& pos) {

	int i = (fin - inicio) / 2;
	if (fin <= inicio) {
		return false;
	}
	if (monomios[i].exponente == exp) {
		pos = i;
		return true;
	}
	if (monomios[i].exponente > exp) {
		return exponenteReptido(exp, i, fin - 1, pos);
	}
	else {
		return exponenteReptido(exp, inicio, i, pos);
	}

}

void Polinomio::AnyadirConOrden(int coef, int exp) {
	int i = num_monomios - 1;
	bool ins = false;
	while (i > 0 && !ins) {
		if (monomios[i - 1].exponente < exp) {
			if (i == num_monomios) {
				monomios[i] = monomios[num_monomios - 1];
			}
			else {
				monomios[i] = monomios[i - 1];
			}
			i--;
		}
		else {
			ins = true;
		}

	}
	if (num_monomios == i) {
		monomios[i].coeficiente = coef;
		monomios[i].exponente = exp;
		return;
	}
	monomios[i].coeficiente = coef;
	monomios[i].exponente = exp;
}

int Polinomio::evaluar(int v)const
{
	int polinomio = 0, potencia = v;

	for (int i = 0; i < num_monomios; i++)
	{
		for (int j = 0; j < monomios[i].exponente; ++i)
		{
			potencia *= v;
		}

		polinomio += potencia * monomios[i].coeficiente;

		potencia = v;
	}

	return polinomio;
}

bool tratar_caso() {

	Polinomio p;

	int n, v, coeficiente, exponente;

	cin >> n >> v;

	if (v == 0 && n == 0)
	{
		return false;
	}

	for (int i = 0; i < 2 * n; ++i)
	{
		cin >> coeficiente >> exponente;

		p.anyadir_monomio(coeficiente, exponente);

	}



	cout << p.evaluar(v) << endl;

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}