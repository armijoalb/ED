/*
 * fecha.h
 *
 * Copyright  (C) Juan F. Huete
*/

#ifndef __FECHA_H
#define __FECHA_H

#include <string>
#include <iostream>

using namespace std;

//! Clase fecha.
/*!
 * \b Constructores
 * fecha::fecha ()

 * \b Sobrecarga de operadores
 * fecha::operator=(), operator==(), operator<(), operator<=(),
 * operator>(), operator>=(), operator!=(), operator<<()

 * \b Modificadores de tipo
 * fecha::toInteger(), stof(), toString().

 * \b Comprobante
 * fecha::check_inv()

 * \b Descripción

 * Contiene toda la información asociada a una fecha con el formato  "mm/dd/aaaa hh:mm:ss AM-PM".
 * Se usará el formato de 12 horas, referenciando la mañana o la tarde con AM o PM.

 * Es necesario compilar con C++11, para ello, se añade la opción -std=c++0x a g++.

 * <b> Función de abstracción </b>

 * Cada unidad temporal de la fecha se instancia en un entero , teniendo:
 * \verbatim
     mes      = mon
     día      = day
     año      = year
     hora     = hour
     minuto   = min
     segundo  = sec
  \endverbatim
 *    El periodo del día (AM o PM) se instancia en un booleano booleano

 * \invariant
 * 1 <=  mon   <= 12
 * 1 <=  day   <= 31
 * year >= 2000
 * 0 <= hour   <= 12
 * 0 <= min    <= 59
 * 0 <= sec    <= 59

 * <b> Ejemplo de uso </b>
 *
 * Crear objeto:
 * \code
 * fecha a;
 * fecha b("mm/dd/aaaa hh:mm:ss AM");
 * fecha c(b);
 * \endcode

 * La sobrecarga del operador = nos permite:
 * \code
 * a = "mm/dd/aaaa hh:mm:ss AM";
 * c = a;
 * \endcode

 * Podemos comparar dos fechas:
 * \code
 * bool t = a > b || a == c;

 * bool g = c <= b || b != a;
 * \endcode

 * Y podemos mostrar una fecha por pantalla:
 * \code
 * cout << a;
 * \endcode

*/
class fecha {

public:

   // Constructor por defecto.
   fecha ();

   // Constructores de copia.
   fecha (const string & s);
   fecha (const fecha & f);

   // Sobrecarga de operadores.
   fecha & operator=(const fecha & f);
   fecha & operator=(const string & s);
   bool operator<(const fecha & f)const;
   bool operator>(const fecha & f) const;
   bool operator<=(const fecha & f)const;
   bool operator>=(const fecha & f) const;
   bool operator==(const fecha & f) const;
   bool operator!=(const fecha & f)const;

   // Invariante de represrentación.
   bool check_inv ();

   //
   string toString() const;

private:

   // Datos miembro
   /**@brief Segundos
   */
   int  sec;

   /**@brief Minutos
   */
   int  min;

   /**@brief Horas
   */
   int  hour;

   /**@brief Día del mes
   */
   int  day;

   /**@brief Mes
   */
   int  mon;

   /**@brief Año
   */
   int  year;

   /**@brief AM/PM
   @post AM = false, PM = true
   */
   bool apm;

   // Conversores de tipos
   int toInteger(const string &s, const int i, const int l);
   void stof(const string &s);

   // Clase amiga para tener acceso a los datos y métodos de la clase.
   friend  ostream& operator<< ( ostream& os, const fecha & f);
};
   // Sobrecarga de la salida estandar.
   ostream& operator<< ( ostream& os, const fecha & f);

#include "fecha.hxx" // Incluimos la implementacion.


#endif
