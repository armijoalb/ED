/*
	Main ( principal.cpp )
	================================

	Programa principal donde se lee el archivo 'crimenes.csv'
	y se trabaja con las distintas estructuras creadas.

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

using namespace std;

	/** 	@brief Lee un fichero de delitos, línea a línea.
			@param[in] s nombre del fichero.
			@param[in,out] C conjunto sobre el que se lee
			@return true si la lectura ha sido correcta, false en caso contrario
	*/

bool load(conjunto &  C, const string & s) {
 ifstream fe;
 string cadena;

 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);

 int linea = 1;

 if (fe.fail())
 {
   cerr << "Error al abrir el fichero " << s << endl;
 } else {
   getline(fe,cadena,'\n'); //leo la cabecera del fichero
   cout << cadena << endl;
    while ( !fe.eof() )
      { getline(fe,cadena,'\n');
       	if (!fe.eof()) {
	   cout << "linea: "<< linea << endl;
	   // Convertir cadena a crimen
           crimen aux = cadena;
           // Insertar cadena en el conjunto
           C.insert(aux);
         }

			++linea;

     }
    fe.close();
    return true;
    } // else
  fe.close();
  return false;
 }

bool load_v2(conjunto &  C, const string & s) {
	ifstream fe;
	string cadena;

	vector<conjunto::entrada> read;

	cout << "Abrimos "<< s << endl;
	fe.open(s.c_str(), ifstream::in);

	if ( fe.fail() )
		cerr << "Error al abrir el fichero " << s << endl;

	else {
		// Leemos la primera cadena del fichero
		getline(fe,cadena,'\n');
		getline(fe,cadena,'\n');

		//cout << cadena << endl;

		int linea = 1;
		while ( !fe.eof() ){
			// Convertir cadena a crimen
			crimen aux = cadena;

			// Mostrar el crimen si queremos
			//cout << aux << endl;

			// Insertar cadena en el conjunto
			read.push_back(aux);

			cout << "Linea: " << linea << endl;
			++linea;

			// Leemos
			getline(fe,cadena,'\n');

		}

		cout << "Añadimos al conjunto..." << endl;

		// Añadimos el vector al conjunto
		C = read;

		cout << "Invariante: " << C.cheq_rep() << endl;

		fe.close();
		return true;

	} // else

	fe.close();
	return false;
}


//-----------------------------------------------------------------------------
//
//		Programa Principal


int main()
{
	conjunto ChicagoBD;
	crimen d;
	fecha f;

	// Cargamos los crímenes
	load_v2(ChicagoBD, "crimenes.csv");

	return 0;
}
