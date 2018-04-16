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
	
	if ( fe.fail() )
		cerr << "Error al abrir el fichero " << s << endl;
		
	else {
		// Leemos la primera cadena del fichero
		getline(fe,cadena,'\n');
		
		cout << cadena << endl;
		
		int linea = 1;
		while ( !fe.eof() ){ 
			// Leemos
			getline(fe,cadena,'\n');
			
			// Si no ha llegado al final
			if ( !fe.eof() ){
				//cout << "leo:: "<< cadena << endl;
				
				// Convertir cadena a crimen
				crimen aux = cadena;
				
				// Mostrar el crimen si queremos
				//cout << aux << endl;
				
				// Insertar cadena en el conjunto
				C.insert(aux);
				
				cout << "Linea: " << linea << endl;
				linea++;
				
			}
		}
		
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
	conjunto ChicagoDB;
	crimen d;
	fecha f;
	
	// Cargamos los crímenes
	load(ChicagoDB, "crimenes.csv");
	
	return 0;
}
