

#include<iostream>
#include<iterator>
#include<cassert>
const int MAX_CHARS = 26;

class ConjuntoChar {
public:
	//ConjuntoChar();
	bool pertenece(char letra) const;
	void anyadir(char letra);
	//O(1)
	ConjuntoChar():num_elems(0) {}
	//O(log_numelems)((llama a busq binaria))
	bool pertenece(char letra) const {//busqueda binaria
		int pos= busquedaBin(0, num_elems, letra);//dev indice
		return pos < num_elems &&  elems[pos] == letra;//Dev true si es menor q numelems O(1)
	}
	//O(n)dnd n  num elems conjunto
	void anyadir(char letra) {
		int pos = busquedaBin(0, num_elems, letra);
		if (pos > num_elems || elems[pos] != letra) {//negacion de lo q te devuelve pertenece=> anadir
			for (int i = num_elems; i > pos; i--) {
				elems[i] = elems[i -1];
			}
			num_elems++;
			elems[pos] = letra;//inserto en pos
		}
		
	}
	
private:
	int num_elems;
	char elems[MAX_CHARS]; 

	//devuelve pos elemento en caso de q este, sino la posicion en la q iria si lo insertasemos(int)
	// coste logaritmivo con respecto a fin - ini
	int busquedaBin(int ini, int fin, char c) const{
		//caso base =vacio ini = fin  1 
		if (ini == fin) return ini;
		else {
			//m dv(fin no incluido, es un elemento mas
		}
	}
};