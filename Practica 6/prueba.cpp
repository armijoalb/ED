/**
* Archivo Prueba de la practica.
* Para compilar, utilizar la opción para c++11.
* g++ -o prueba prueba.cpp -Wall -std=c++0x
* Alberto Armijo Ruiz.
* 2º GII A.
*/

#include "avl.h"
#include <iostream>
#include <functional>

using namespace std;

int main(){

  AVL<int > el_avl;

  cout << "Prueba empty" << endl;
  if( el_avl.empty() )
    cout << "Está vacío" << endl;

  cout << "Prueba size " << endl;
  cout << el_avl.size() <<endl;

  el_avl.clear();

  cout << "prueba_insert" << endl;

  el_avl.insert(4);
  el_avl.insert(5);
  el_avl.insert(2);
  el_avl.insert(3);
  el_avl.insert(1);
  el_avl.insert(0);

  cout << "Prueba reverse_iterator" << endl;
  for( auto it2 = el_avl.rbegin() ; it2 != el_avl.rend() ; ++it2 ){
    cout << *it2 << ' ';
  }

  cout << endl;

  cout << "Prueba find" << endl;
  auto it = el_avl.find(5);
  cout << *it << endl;

  cout << "Prueba erase " << endl;
  el_avl.erase(it);

  for( auto it2 = el_avl.begin(); it2 != el_avl.end(); ++it2 ){
    cout << *it2 << ' ';
  }

  cout << endl ;

  cout << "Prueba lower_bound " << endl;
  it = el_avl.lower_bound(2);

  cout << *it << endl;

  cout << "Prueba upper_bound" << endl;
  it = el_avl.upper_bound(2);
  cout << *it << endl;

  cout << "Prueba iterator " << endl;
  it = el_avl.begin();
  while( it != el_avl.end() ){
    cout << *it << ' ';
    ++it;
  }

  AVL<int> otro_avl;

  otro_avl.insert(1);
  otro_avl.insert(4);
  otro_avl.insert(-2);
  otro_avl.insert(7);

  cout << "Prueba swap " << endl;

  el_avl.swap( otro_avl );

  for( auto it2 = el_avl.begin(); it2 != el_avl.end(); ++it2 ){
    cout << *it2 << ' ';
  }

  cout << endl;

  cout << "Prueba operación de asignación " << endl;
  el_avl = otro_avl;
  for( auto it2 = el_avl.begin(); it2 != el_avl.end() ; ++it2 ){
    cout << *it2 << ' ' ;
  }

  cout << endl;
  cout << "FIN fichero prueba" << endl;
  return 0;
}
