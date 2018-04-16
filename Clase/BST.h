// BST: árbol binario de busqueda.

#ifndef __BST_H
#define __BST_H

template <typename K, typename T>
class BST{
private:
  bintree<pair<K,T> arbolt;
  unsigned int tama;

public:
  void insert( const pair<K,T> & val);
  void erase( const K & k );
  class iterator{
  private:
    bintree<pair<K,T> >::node nodo;
  };
  BST<K,T>::iterator begin();
  BST<K,T>::iterator find( cosnt K & k);
};

#include "BST.hxx"
#endif
