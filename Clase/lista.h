#ifndef __LISTA_H_
#define __LISTA_H_

template < typename T>
class list{
private:
  struct node{
    node *sig;
    T info;
    node *ant;
  }
  node * cub;
  unsigned int tama;
public:
  list();
  ~list();
  unsigned int size() const;
  bool empty() const;
  T & back();
  const T & back();
  void push_back( const T & dato );
  void pop_back();
  void clear();
  void remove( const T & dato );

  iterator insert( iterator pos, const T & x );
  void insert( iterator it, unsigned int n, const T & x );
  template < class InputIterator >
  void insert( iterator it, InputIterator ini, InputIterator fin);

  // ---------------------------------------------------------------------------------
  // clase iterator.
  // ---------------------------------------------------------------------------------
  class iterator{
  public:
    iterator();
    iterator( const list<T>::iterator & it );
    list<T>::iterator & operator++;
    bool operator == ( const list<T>::iterator & it )const;
  private:
    node * ptr_nodo;
  };

  list<T>::begin();
  list<T>::end();


}

#include "lista.hxx"
#endif
