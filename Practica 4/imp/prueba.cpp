/*
	Archivo de prueba ( prueba.cpp )
	================================

	Archivo para probar el correcto funcionamiento de las
	diferentes clases.

	Integrantes del grupo:

	- Alberto Sola Comino
	- Alberto Armijo Ruiz
	- Adrián de la Torre Rodríguez
	- Pablo Rey Pedrosa

	2015 / 2016 - 2ºA

*/

#include "conjunto.h"
#include "crimen.h"
#include "fecha.h"
#include <iostream>
#include <fstream>
#include <functional>


int main(){


	conjunto< less<crimen> > prueba;
	conjunto< less<crimen> > prueba_2( prueba );
	conjunto< less<crimen> > prueba_3;
	vector<crimen> v_crimenes;

	prueba_3 = v_crimenes;

	cout << prueba.size() << endl;

   cout << "FIN" << endl;
}
