/**
*   TDA AVL
*   Cabeceras del AVL.
*   Hecho por Alberto Armijo Ruiz.
*   2º GII A.
*/

#ifndef __AVL_H
#define __AVL_H

#include "bintree.h"
#include "functor.h"
#include <utility>
#include <functional>
#include <algorithm>

template <typename T, class comparar = std::less<T> >

// Clase AVL.
class AVL{
  public:
    typedef int altura; // Tipo para definir la altura de un nodo en el árbol.
    typedef unsigned int size_type;

    // Constructores.
    AVL();
    AVL( const AVL<T,comparar> & copy_avl );

    // Operadores de asignación.
    AVL & operator = ( const AVL<T, comparar> & avl_asig );

    // Consultores capacidad.
    bool empty() const;
    size_type size() const;


    //------------------------------------------------
    //    Clase iterator.
    //------------------------------------------------
    class iterator{
      private:
        friend class AVL;
        typename bintree<std::pair<T, altura> >::inorder_iterator mi_it;
      public:
        iterator();
        iterator( const typename bintree<std::pair<T, altura> >::inorder_iterator & it);
        iterator( const AVL<T,comparar>::iterator & it );
        iterator( typename bintree<T>::node & n );
        bool operator ==( const typename AVL<T,comparar>::iterator & it);
        bool operator !=( const typename AVL<T,comparar>::iterator & it);
        T & operator *();
        AVL::iterator & operator ++();
    };

    // Métodos de iterator.
    AVL<T,comparar>::iterator begin();
    AVL<T,comparar>::iterator end();


    //--------------------------------------------------
    //    Clase const_iterator.
    //--------------------------------------------------
    class const_iterator{
      private:
        typename bintree<std::pair<T, altura> >::const_inorder_iterator mi_it;
      public:
        const_iterator();
        const_iterator( const typename bintree<std::pair<T, altura> >::const_inorder_iterator & it );
        const_iterator( const typename bintree<std::pair<T, altura> >::inorder_iterator & it);
        const_iterator( const AVL<T,comparar>::const_iterator &it);
        const_iterator( const AVL<T,comparar>::iterator & it);
        bool operator ==( const typename AVL<T,comparar>::const_iterator & it ) const;
        bool operator !=( const typename AVL<T,comparar>::const_iterator & it ) const;
        const T & operator *() const;
        AVL::const_iterator & operator ++();
    };

    // Métodos de const_iterator.
    AVL<T,comparar>::const_iterator cbegin() const;
    AVL<T,comparar>::const_iterator cend() const;

    //---------------------------------------------------
    //  Clase reverse_iterator.
    //---------------------------------------------------
    class reverse_iterator{
      private:
        typename bintree<std::pair<T, altura> >::inorder_iterator mi_r_it; //Inorden del revés.
      public:
        reverse_iterator();
        reverse_iterator( const AVL<T,comparar>::reverse_iterator & it);
        reverse_iterator( const typename bintree<std::pair<T, altura> >::inorder_iterator & it);
        bool operator ==( const typename AVL<T,comparar>::reverse_iterator & it);
        bool operator !=( const typename AVL<T,comparar>::reverse_iterator & it);
        T & operator *();
        AVL::reverse_iterator & operator ++();
    };

    // Métodos de reverse_iterator.
    AVL<T,comparar>::reverse_iterator rbegin();
    AVL<T,comparar>::reverse_iterator rend();


    //-----------------------------------------------------
    //    Clase const_reverse_iterator.
    //-----------------------------------------------------
    class const_reverse_iterator{
      private:
        typename bintree<std::pair<T, altura> >::const_inorder_iterator mi_r_it; // Inorden del revés.
      public:
        const_reverse_iterator();
        const_reverse_iterator( const AVL<T,comparar>::const_reverse_iterator & it);
        const_reverse_iterator( const typename bintree<std::pair<T, altura> >::const_inorder_iterator & it);
        bool operator ==( const typename AVL<T,comparar>::const_reverse_iterator & it ) const;
        bool operator !=( const typename AVL<T,comparar>::const_reverse_iterator & it ) const;
        const T & operator *() const;
        AVL::const_reverse_iterator & operator ++();
    };

    // Métodos de const_reverse_iterator.
    AVL<T,comparar>::const_reverse_iterator crbegin();
    AVL<T,comparar>::const_reverse_iterator crend();


    // Modificadores.
    std::pair<AVL<T,comparar>::iterator, bool > insert( const T & e );
    void erase( typename AVL<T,comparar>::iterator & it );
    void swap( AVL<T, comparar> & dest );
    void clear();

    // Operaciones.
    bool find( const T & e, typename bintree<std::pair<T,altura> >::node &n, typename bintree<std::pair<T,altura> >::node &padre) const;
    AVL<T,comparar>::iterator find( const T & e);
    AVL<T,comparar>::iterator upper_bound( const T & e);
    AVL<T,comparar>::iterator lower_bound( const T & e);

    void rsi( typename bintree< std::pair<T, altura> >::node & n );
    void rsd( typename bintree< std::pair<T, altura> >::node & n );
    void rdi( typename bintree< std::pair<T, altura> >::node & n );
    void rdd( typename bintree< std::pair<T, altura> >::node & n );

    void balancear_arbol( typename bintree< std::pair<T, altura> >::node & n ); // Hacer private despues.

  private:
    altura h( typename bintree< std::pair<T,altura> >::node & n);
    altura h( typename bintree< std::pair<T, altura> >::const_node & n) const;
    int balanceo( const typename bintree< std::pair<T, altura> >::node & n );

    bintree<std::pair<T, altura> > el_avl;
    unsigned int tama;
    comparar cmp;

};


#include "avl.hxx"

#endif
