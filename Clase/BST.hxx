// Implementación BST.

template < typename K, typename T >
typename BST<K,T>::iterator BST<K,T>::begin(){
  typename BST<K,T>::iterator sal;
  sal.nodo = arbolt.root();
  while( !sal.nodo.left().null() )
    sal.nodo = sal.nodo.left();

  return sal;
}

template < typename K, typename T>
typename BST<K,T>::iterator BST<K,T>::find( const K & k ){
  bool encontrado = false;
  bintree<pair<K,T> >::node n;
  n = arbolt.root();

  while( !encontrado && !n.null() ){
    if( (*n).first == k ){
      encontrado = true;

    }
    else if( (*n).first < k ){
      n =  n.right();
    }
    else{
      n = n.left();
    }
  }

  return typename BST<K,T>::iterator( n );
}

template < typename K, typename T>
void BST<K,T>::insert( const pair<K,T> & val){
  bintree<pair<K,T> >::node n = arbolt.root();
  bool encontrado = false;

  if( n.null() ){
    arbolt.set_root( value );
    tama ++;
  }
  else{
    while( !encontrado ){
      if( (*n).first == value.first ){
        encontrado = true;
        (*n).second = value.second;
      }
      else if( (*n).first < value.first ){
        if( !n.right().null() )
          n = n.right();
        else
          encontrado = true;
      }
      else{
        if( !n.left().null() )
          n = n.left();
        else
          encontrado = true;
      }
    }

    if( (*n).first != value.first ){
      if( (*n).first < value.first )
        arbolt.insert_right( n, value );
      else
        arbolt.insert_left( n, value );

      tama ++;
    }
  }
}

template <typename K, typename T>
void BST<K,T>::erase( const K & k ){
  bintree<pair<K,T> >::node n = arbolt.root();
  bool encontrado = false;

  while( !encontrado && !n.null() ){
    if((*n).first == k ){
      encontrado = true;
    }
    else if( (*n).first < k ){
      n.right();
    }
    else{
      n.left();
    }
  }

  if( n.null() )
    return 0;
  else{
    // Caso hoja.
    if( ( n.right().null() ) && ( n.left().null() ) ){
      // Es raíz.
      if( n.parent().null() ){
        arbolt.clear();
      }
      else if( *( n.parent() ).first < k ){
        bintree<pair<K,T> > dest;
        arbolt.prune_right( n.parent(), dest);
        dest.clear();
      }
      else{
        bintree<pair<K,T> > dest;
        arbolt.prune_left( n.parent() , dest);
        dest.clear();
      }
    }
  }
  else if( n.left().null() || n.right().null() ){
    if( n.left().null() ){
      // Es hijo derecha.
      arbolt.prune_right( n, dest);
      if( n.parent().null() )
        arbolt.assign_tree( dest );
      else if( *(n.parent()).first < k )
          arbolt.insert_right( n.parent(), dest );
        else
          arbolt.insert_left( n.parent(), dest );
    }
  }

  tama --;
}
