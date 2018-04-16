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


int main(){


	conjunto prueba;

	string linea = "10230953,HY418703,09/10/2015 11:56:00 PM,048XX W NORTH AVE,0498,BATTERY,AGGRAVATED DOMESTIC BATTERY: HANDS/FIST/FEET SERIOUS INJURY,APARTMENT,true,true,2533,025,37,25,04B,1143637,1910194,2015,09/17/2015 11:37:18 AM,41.909605035,-87.747777145,\"(41.909605035, -87.747777145)\"" ;
	crimen aux = linea ;
	prueba.insert( aux );

	linea = "10230979,HY418750,09/10/2015 11:55:00 PM,120XX S PARNELL AVE,0486,BATTERY,DOMESTIC BATTERY SIMPLE,ALLEY,true,true,0523,005,34,53,08B,1174806,1825089,2015,09/17/2015 11:37:18 AM,41.675427135,-87.63581257,\"(41.675427135, -87.63581257)\"" ;
	aux = linea ;
	prueba.insert( aux );

	linea = "10231208,HY418843,09/10/2015 11:50:00 PM,021XX W BERWYN AVE,0820,THEFT,$500 AND UNDER,STREET,false,false,2012,020,40,4,06,1161036,1935171,2015,09/17/2015 11:37:18 AM,41.97779966,-87.683164484,\"(41.97779966, -87.683164484)\"" ;
	aux = linea ;
	prueba.insert( aux );

	/////////////////////////
	//
	//		conjunto::iterator
	//
	////////////////////////

	conjunto::iterator ini = prueba.begin();
	conjunto::iterator fin = prueba.end();

	cout << "conjunto::iterator" << endl << endl;

	while( ini != fin ){

		cout << "Conjunto entrada" << endl;

		cout << *ini << endl;

		cout << endl;

		++ini;

	}

	/////////////////////////
	//
	//		conjunto::const_iterator
	//
	////////////////////////


	conjunto::const_iterator cini = prueba.cbegin();
	conjunto::const_iterator cfin = prueba.cend();

	cout << "conjunto::const_iterator" << endl << endl;

	while( cini != cfin ){

		cout << "Conjunto entrada" << endl;

		cout << *cini << endl;

		cout << endl;

		++cini;

	}


   //////////////////////////////////
	//
	// conjunto::description_iterator
	//
	//////////////////////////////////


	conjunto::description_iterator dini = prueba.dbegin("FIST");
	conjunto::description_iterator dfin = prueba.dend("FIST");

	cout << "conjunto::description_iterator" << endl << endl;

	while( dini != dfin ){

		cout << "Conjunto entrada" << endl;

		cout << *dini << endl;

		cout << endl;

		++dini;

	}

   ////////////////////////////////////////
	//
	// conjunto::const_description_iterator
	//
	////////////////////////////////////////


	conjunto::const_description_iterator cdini = prueba.cdbegin("BATTERY");
	conjunto::const_description_iterator cdfin = prueba.cdend("BATTERY");

	cout << "conjunto::const_description_iterator" << endl << endl;

	while( cdini != cdfin ){

		cout << "Conjunto entrada" << endl;

		cout << *cdini << endl;

		cout << endl;

		++cdini;

	}


   //////////////////////////////////
	//
	// conjunto::arrest_iterator
	//
	//////////////////////////////////


	conjunto::arrest_iterator aini = prueba.abegin();
	conjunto::arrest_iterator afin = prueba.aend();

	cout << "conjunto::arrest_iterator" << endl << endl;

	while( aini != afin ){

		cout << "Conjunto entrada" << endl;

		cout << *aini << endl;

		cout << endl;

		++aini;

	}

   ////////////////////////////////////////
	//
	//   conjunto::const_arrest_iterator
	//
	////////////////////////////////////////


	conjunto::const_arrest_iterator caini = prueba.cabegin();
	conjunto::const_arrest_iterator cafin = prueba.caend();

	cout << "conjunto::const_arrest_iterator" << endl << endl;

	while( caini != cafin ){

		cout << "Conjunto entrada" << endl;

		cout << *caini << endl;

		cout << endl;

		++caini;

	}

   cout << "FIN" << endl;
}
