/*
 * crimen.h
 *
 * Copyright  (C) Juan F. Huete
*/
#ifndef __CRIMEN_H
#define __CRIMEN_H

#include <string>
#include <iostream>
#include <vector>
#include "fecha.h"

using namespace std;

//! Clase crimen, asociada a la definición de un crimen.
/*!
	\b Constructores

	crimen::crimen()

	\b Consultores

	crimen::getID(), getCaseNumber(), getDate(), getIUCR(),
	getPrimaryType(), getDescription(), getLocationDescription(),
	getArrest(), getDomestic(), getLatitude(), getLongitude()


	\b Modificadores

	crimen::setID(), setCaseNumber(), setDate(), setIUCR(),
	setPrimaryType(), setDescription(), setLocationDescription(),
	setArrest(), setDomestic(), setLatitude(), setLongitude()


	<b> Sobrecarga de operadores </b>

	crimen::operator=(), operator==(), operator!=(), operator<(),
	operator<=(), operator>(), operator>=(), operator<<()


 * \b Descripción

 * Contiene toda la información asociada a un crimen.

 * <b>Requiere C++11 ( Flag: -std=c++0x )</b>

 * El ID por defecto es 1.

 * Los atributos de un objeto crimen son:


 * \li ID : Número ( mayor que 0 ) que identifica el caso ( es único ).
 *	\li Número del caso
 *	\li Fecha
 *	\li IUCR
 *	\li Tipo de crimen
 *	\li Descripción
 *	\li Localización ( descripción )
 *	\li Ha habido arrestos
 *	\li Es doméstico
 *	\li Latitud / Longitud


	\invariant

* El invariante de la representación del crimen es su ID de forma que:

	\verbatim

	IR: rep ==> bool

	 Para todo crimen:
			ID > 0
	\endverbatim


	<b> Sobrecarga de operadores </b>

	Están sobrecargados los operadores de comparación y el de la salida estándar ( << ).
	El criterio de comparación es el ID, que al ser único y un entero es fácil determinar
	cuál es menor y por tanto sucedió antes cronológicamente.


 * <b> Ejemplo de uso: </b>
 \code

 // Crea un objeto crimen vacío.
 crimen input_crimen, output_crimen;

 // Creamos los parámetros.
 long int id = ... ;
 ...

 // Rellenamos los datos.
 input_crimen.setID( id )
 ...

 // Ahora podemos copiarlo
 output_crimen = input_crimen;
 crimen otro_crimen( output_crimen );

 // O también obtener datos.
 cout << otro_crimen.getCaseNumber();

 // Podemos mostrar un crimen por la salida estándar
 cout << input_crimen << otro_crimen;

 // O compararlos entre sí
 if( input_crimen < otro_crimen )
 	cout << "El primer crimen fue: " << input_crimen << endl;

 \endcode

*/

class crimen {
	public:

		//////////////////////////
		//
		//        CRIMEN
		//
		//////////////////////////

		crimen();
		crimen( const crimen & x );
		crimen(	long int id, 						// ID del caso
					const string & cas_num,			// Nº del caso
					const fecha & dat,				// Fecha del caso
					const string & iu,				// IUCR
					const string & prim_type,		// Tipo primario del caso
					const string & desc,				// Descripción
					const string & loc_des,			// Localización ( string )
					bool arr,							// Ha habido arrestos
					bool dom,							// Es un caso doméstico
					double lat,							// Latitud
					double lon							// Longitud
		);
		crimen( const string & data );
		
		// Comprobar el invariante
		bool cheq_rep();


		/////////////////////////
		//
		//     MODIFICADORES
		//
		/////////////////////////


		void setID( long int id );
		void setCaseNumber( const string & case_num );
		void setDate( const fecha & dat );
		void setIUCR( const string & iucr_dat );
		void setPrimaryType( const string & p_type);
		void setDescription( const string & des );
		void setLocationDescription( const string & loc_des );
		void setArrest( bool arr );
		void setDomestic( bool dom );
		void setLatitude( double lat );
		void setLongitude( double lon );

		void setFromString( const string & data );

		/////////////////////////
		//
		//     CONSULTORES
		//
		/////////////////////////


		long int getID() const;
		const string & getCaseNumber() const;
		const fecha & getDate() const;
		const string & getIUCR() const;
		const string & getPrimaryType() const;
		const string & getDescription() const;
		const string & getLocationDescription() const;
		bool getArrest() const;
		bool getDomestic() const;
		double getLatitude() const;
		double getLongitude() const;


		/////////////////////////
		//
		//     Sobrecarga
		//
		/////////////////////////



		crimen & operator=(const crimen & c);
		crimen & operator=( const string & data );
		bool operator==(const crimen & c) const;
		bool operator!=(const crimen & c) const;
		bool operator<(const crimen & c) const;
		bool operator<=(const crimen & c) const;
		bool operator>(const crimen & c) const;
		bool operator>=(const crimen & c) const;

	private:

		friend ostream & operator<< ( ostream & os, const crimen & c );

		//Atributos
		long int ID; 							// ID del caso
		string case_number;					// Nº del caso
		fecha date;								// Fecha del caso
		string iucr;							// IUCR - Código del tipo del delito según Illinois Uniform Crime Reporting
		string primary_type;					// Tipo primario del caso
		string description;					// Descripción
		string location_description;		// Localización ( string )
		bool arrest;							// Ha habido arrestos
		bool domestic;							// Es un caso doméstico
		double latitude;						// Latitud
		double longitude;						// Longitud
};

ostream & operator<< ( ostream & os, const crimen & c );


#include "crimen.hxx"
#endif
