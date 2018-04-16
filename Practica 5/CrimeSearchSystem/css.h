/**
  * CrimeSearchSystem
  *
  * Alberto Armijo Ruiz.
  * 2º GII A.
*/

#ifndef __CSS_H
#define __CSS_H

#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <utility>
#include <list>
#include <iostream>
#include <queue>

#include "crimen.h"

using namespace std;

// Clase CSS. Maneja la base de datos de crímenes de chicago.

// Tipos definidos para la clase.
typedef float Longitud;
typedef float Latitud;
typedef unsigned int ID;
typedef crimen Crimen;
typedef string Termino;
typedef string IUCR;
typedef fecha Date;

class CSS{
private:
  friend class IUCR_iterator;
  map<ID,Crimen> baseDatos;
  multimap<Date, map<ID,Crimen>::iterator  > DateAccess;
  map<IUCR,set<ID> > IUCRAccess;
  unordered_map<Termino, set<ID> > index;
  map<Longitud, multimap<Latitud, ID> > posicionesGeo;

public:
  // Métodos básicos.
  CSS();
  void load( string nombreDB );
  void insert( const Crimen & x);
  bool erase( ID id );
  void setArrest( const ID id, bool value );

  // Métodos Consulta libre.
  vector<pair<ID,float> > Query( list<string> & q, int k);
  void unionPeso( map<ID, float> & m, const set<ID> & t_i );

  // Método inArea.
  list<ID> inArea( Longitud x1, Latitud y1, Longitud x2, Latitud y2 );

  //--------------------------------------
  // iterator.
  //--------------------------------------
  class iterator{
  private:
    friend class CSS;
    map<ID, Crimen>::iterator it;
  public:
    iterator();
    iterator( const map<ID, Crimen>::iterator & iter );
    std::pair<const ID, Crimen> & operator *();
    bool operator != (const CSS::iterator & iter);
    bool operator == (const CSS::iterator & iter);
    CSS::iterator & operator ++();
    CSS::iterator & operator --();
    CSS::iterator operator ++(int);
    CSS::iterator operator --(int);
  };

  // Métodos con salida CSS::iterator.
  CSS::iterator find_ID( const ID id );
  CSS::iterator begin();
  CSS::iterator end();

  //--------------------------------------
  // IUCR_iterator.
  //--------------------------------------
  class IUCR_iterator {
  private:
    // it_m itera sobre los IUCR del map

    map<IUCR,set<ID> >::iterator it_m;
    // it_s itera sobre los ID del set

    set<ID>::iterator it_s;
    // Referencia a baseDatos.
    CSS & parent;
  public:
    IUCR_iterator(CSS & p);
    IUCR_iterator( const map<IUCR,set<ID> >::iterator & iter_m , CSS & p);
    CSS::IUCR_iterator & operator ++();
    CSS::IUCR_iterator & operator --();
    bool operator !=( const CSS::IUCR_iterator & iter);
    bool operator ==( const CSS::IUCR_iterator & iter);
    std::pair<const ID, Crimen > & operator*();
  };

  // Métodos con salida CSS::IUCR_iterator.
  CSS::IUCR_iterator ibegin();
  CSS::IUCR_iterator iend();
  CSS::IUCR_iterator lower_bound(IUCR iucr);
  CSS::IUCR_iterator upper_bound(IUCR iucr);

  //--------------------------------------
  // Date_iterator.
  //--------------------------------------
  class Date_iterator {
  private:
    friend class CSS;
    multimap<Date, map<ID,Crimen>::iterator >::iterator it_mm;
  public:
    Date_iterator();
    Date_iterator( const multimap<Date, map<ID, Crimen>::iterator >::iterator & iter);
    CSS::Date_iterator & operator ++();
    CSS::Date_iterator & operator --();
    CSS::Date_iterator operator ++(int);
    CSS::Date_iterator operator --(int);
    bool operator != ( const CSS::Date_iterator & iter);
    bool operator == ( const CSS::Date_iterator & iter);
    std::pair<const ID, Crimen > & operator*();
  };

  // Métodos con salida CSS::Date_iterator.
  CSS::Date_iterator dbegin();
  CSS::Date_iterator dend();
  CSS::Date_iterator lower_bound(Date fecha);
  CSS::Date_iterator upper_bound(Date fecha);

  // Functor para comparar objetos de la priority_queue.
  class my_comp{
  public:
    bool operator() (const std::pair<ID, float> & lhs, const std::pair<ID, float> & rhs) const;

  };

};

#include "css.hxx"
#endif
