/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
using namespace std;
using Duracion = int;
class Hora {
public:
	Hora(int horas, int minutos, int segundos):
    num_segundos(horas*3600+minutos*60 +segundos){}

	int horas()const{
		return num_segundos / 3600;
	}
	int min()const {
		return (num_segundos % 3600)/60;
	}
	int seg()const {
		return num_segundos % 60;
	}

	Hora suma(Duracion duracion)const {
		Hora resultado(0, 0, 0);
		resultado.num_segundos = num_segundos + duracion;
		return resultado;
	}
	Duracion resta(Hora hora) const{
		return hora.num_segundos - num_segundos;
	}

private:
	
	int num_segundos;
};
//O(1) 
Hora hora_pastilla(const Hora& primera, const Hora& ultima, int num_pastillas, int i) {
	int dur= primera.resta(ultima);
	if (dur < 0) {// 22::00 - 05::00
		dur += 3600 * 24;//dur en segundos
	}
	int durEntrePas = dur /( num_pastillas - 1);

	return primera.suma(durEntrePas * (i - 1));
}
void imprimir(const Hora &h) {

}
int main() {

}
