/**
  Contenedor árbol binario (bintree).
  Plantilla.
  Alberto Armijo Ruiz.
  2º A GII.
*/

#ifndef __BINTREE_H
#define __BINTREE_H

#include <vector>

typedef unsigned int size_type;

template<typename T>
class bintree{
public:
  // Constructores.
  bintree();
  bintree( const T & e );
  bintree( const bintree<T> &A );

  // Destructor.
  ~bintree();

  // Operador de asignación.
  bintree<T> & operator = ( const bintree<T> &A );

  // Clase nodo.
  class node{
  private:
    T etiqueta;
    bintree<T>::node * padre;
    bintree<T>::node * izquierda;
    bintree<T>::node * derecha;
  public:
    // Constructores.
    node();
    node( const typename bintree<T>::node &n);

    // Asignación.
    node & operator = ( const typename bintree<T>::node &n );

    // Consultores.
    bool null() const;
    bool esHoja() const;
    bool esInterno() const;

    bintree<T>::node * parent() const;
    bintree<T>::node * left() const;
    bintree<T>::node * right() const;

    T & operator *();

    // Comparadores.
    bool operator == ( const  typename bintree<T>::node &n ) const;
    bool operator != ( const typename bintree<T>::node &n ) const;
  };

  // Consultores.
  bintree<T>::node * root() const;
  bool null() const;
  size_type size() const;

  // Otros métodos.
  void prune_right( bintree<T>::node n, bintree<T> dest );
  void prune_left( bintree<T>::node n, bintree<T> dest );
  void insert( node *& root, T & x );

  // Asignación de un subárbol.
  void assign_subtree( const bintree<T> &A, const bintree<T>::node &n );

private:
  bintree<T>::node * raiz;
  size_type num_nodos;


};

#include "bintree.hxx"

#endif
