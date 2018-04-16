#include <iostream>
#include "bintree.h"
using namespace std;

int main(){
  // -----------------------------------------------------------------------------------------------
  /*
  bintree<int>::node n;

  bintree<int>::node n2(n);

  if( n.esHoja() )
    cout << "no tiene hijos" << endl;

  if( n == n2 )
    cout << "son iguales " << endl;

  if( !( n != n2 ) ){
    cout << "no son iguales" << endl;
  }

  bintree<int>::node * izq = n.left();
  if( izq->null() )
    cout << "nulo" << endl;

  cout << *n << endl << *n2 << endl;
  */
  // -----------------------------------------------------------------------------------------------

  bintree<int> a;
  cout << a.size() << endl;


  return 0;
}
