/**
 * Archivo de prueba del conjunto.
 *
 * Alberto Armijo Ruiz.
 * 2º GII A.
 *
*/

#include "css.h"
#include <iostream>
using namespace std;

int main(){
  CSS CrimenesChicago;

  cout << "Cargando conjunto de Crimenes." << endl;
  CrimenesChicago.load("crimenes.csv");

  cout << "Primer elemento del conjunto." << endl;

  // ----------------------------------------------------------------------------------------------------------------------
  // Comprobación métodos iterator.
  // ----------------------------------------------------------------------------------------------------------------------

  CSS::iterator it = CrimenesChicago.begin();
  cout << (*it).first << endl;
  cout << (*it).second << endl;

  it++;
  it++;
  cout << (*it).first << endl;
  cout << (*it).second << endl;

  // ----------------------------------------------------------------------------------------------------------------------
  // Comprobación método erase.
  // ----------------------------------------------------------------------------------------------------------------------

  cout << "Borramos el primer elemento del conjunto." << endl;
  CrimenesChicago.erase( (*it).first );

  it = CrimenesChicago.begin();

  cout << (*it).first << endl;
  cout << (*it).second << endl;
  // ----------------------------------------------------------------------------------------------------------------------
  // Comprobación método find_ID.
  // ----------------------------------------------------------------------------------------------------------------------

  CSS::iterator iter = CrimenesChicago.find_ID( 21844 );
  if( iter == CrimenesChicago.end() )
    cout << "El elemento no se encuentra en el conjunto." << endl;

  iter = CrimenesChicago.find_ID( 21845 );
  cout << (*iter).second << endl;

  // ----------------------------------------------------------------------------------------------------------------------
  // Comprobación método setArrest.
  // ----------------------------------------------------------------------------------------------------------------------

  cout << "Comprobación método setArrest" << endl;
  CrimenesChicago.setArrest( (*iter).first, true);
  cout << (*iter).second << endl;

  // ----------------------------------------------------------------------------------------------------------------------
  // Comprobación métodos Date_iterator.
  // ----------------------------------------------------------------------------------------------------------------------

  CSS::Date_iterator date_it = CrimenesChicago.dbegin();

  cout << "Prueba Date_iterator:" << endl << endl;
  cout << (*date_it).first << endl;
  cout << (*date_it).second << endl;

  date_it ++;

  cout << (*date_it).first << endl;
  cout << (*date_it).second << endl;

  date_it --;

  cout << (*date_it).first << endl;
  cout << (*date_it).second << endl;

  // ----------------------------------------------------------------------------------------------------------------------
  // Prueba IUCR_iterator.
  // ----------------------------------------------------------------------------------------------------------------------

  cout << "Prueba IUCR_iterator:" << endl << endl;
  CSS::IUCR_iterator it_iucr = CrimenesChicago.ibegin();
  cout << (*it_iucr).first << endl;
  cout << (*it_iucr).second << endl;

  ++it;

  cout << (*it_iucr).first << endl;
  cout << (*it_iucr).second << endl;

  --it;
  cout << (*it_iucr).first << endl;
  cout << (*it_iucr).second << endl;

  // ----------------------------------------------------------------------------------------------------------------------
  // Prueba método inArea.
  // ----------------------------------------------------------------------------------------------------------------------

  cout << "Prueba método inArea:" << endl << endl;

  list<ID> in_area;
  in_area = CrimenesChicago.inArea( -87.7311, 41.7496, -87.5928,41.867 );
  char res;
  cout << "¿Mostrar resultado? [S/s]:" << endl;
  cin >> res;

  if(res == 's' || res == 'S'){
    for( list<ID>::iterator it_s = in_area.begin() ; it_s != in_area.end() ; it_s ++){
      cout << *it_s << endl;
    }
  }

  // ----------------------------------------------------------------------------------------------------------------------
  // Prueba unionPeso.
  // ----------------------------------------------------------------------------------------------------------------------

  cout << "Prueba unionPeso." << endl;

  set<ID> t1, t2;
  for( int i = 0 ; i < 10 ; i++){
    t1.insert(i);
  }
  for( int i = 0 ; i < 20 ; i+=2){
    t2.insert( i);
  }


  map<ID, float> prueba_union;
  CrimenesChicago.unionPeso( prueba_union, t1);
  CrimenesChicago.unionPeso( prueba_union, t2);

  set<ID> t3;
  for( int i = 0 ; i < 20 ; i++){
    t3.insert(i);
  }

  CrimenesChicago.unionPeso( prueba_union, t3);

  map<ID, float>::iterator it_mapa;
  it_mapa = prueba_union.begin();

  while( it_mapa != prueba_union.end() ){
    cout << (*it_mapa).first << ' ' << (*it_mapa).second << endl;
    it_mapa++;
  }

  // ----------------------------------------------------------------------------------------------------------------------
  // Prueba Query.
  // ----------------------------------------------------------------------------------------------------------------------

  list<string> li;
  li.push_back("AGGRAVATED");
  li.push_back("BATTERY:");
  li.push_back("OTHER");
  li.push_back("DANG");
  li.push_back("WEAPON");
  li.push_back("THEFT");
  li.push_back("SIMPLE");
  li.push_back("DOMESTIC");
  li.push_back("INJURY");
  int k = 5;


  cout << endl << endl << "Prueba con 2 elementos." << endl;

  list<string>::iterator it_l = li.begin();
  for( ; it_l != li.end() ; it_l ++){
    cout << *it_l << endl;
  }

  vector<pair<ID, float> > prueba_query( CrimenesChicago.Query( li, k ) );

  for( int i = 0; i < k ; i++ ){
    cout << prueba_query[i].first << ' ' << prueba_query[i].second << endl;
  }

  return 0;
}
