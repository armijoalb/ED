#include <algorithm>

// -----------------------------------------------------------------------------
// Implementación métodos conjunto.
// -----------------------------------------------------------------------------

// Constructor por defecto.
template < class CMP >
conjunto<CMP>::conjunto(){}

// Constructor de copia.
template < class CMP >
conjunto<CMP>::conjunto( const conjunto<CMP> & d){
  this->vc   = d.vc;
  this->comp = d.comp;
}

// Constructor de copia con vector.
template < class CMP >
conjunto<CMP>::conjunto( vector< typename conjunto<CMP>::entrada> & v_entrada ){
  this->vc = v_entrada;
}

// Consultor del tamaño.
template < class CMP >
typename conjunto<CMP>::size_type conjunto<CMP>::size()const{
  return vc.size();
}


// --------------------------------------------------------------------------------------------
// Funciones lower_bound.
// --------------------------------------------------------------------------------------------

template < class CMP >
typename conjunto<CMP>::iterator conjunto<CMP>::lower_bound( const typename conjunto<CMP>::entrada &x ){
  typename conjunto<CMP>::iterator sal( lower_bound( vc.begin(), vc.end(), x, comp ) );

  return sal;
}

template < class CMP >
typename conjunto<CMP>::const_iterator conjunto<CMP>::lower_bound( const typename conjunto<CMP>::entrada &x ) const{
  typename conjunto<CMP>::const_iterator sal( lower_bound( vc.begin(), vc.end(), x, comp) );

  return sal;
}

// ------------------------------------------------------------------------------------------------
// Funciones upper_bound.
// ------------------------------------------------------------------------------------------------
template < class CMP >
typename conjunto<CMP>::iterator conjunto<CMP>::upper_bound( const typename conjunto<CMP>::entrada &x ){
  typename conjunto<CMP>::iterator sal( upper_bound( vc.begin(), vc.end(), x, comp) );

  return sal;
}

template < class CMP >
typename conjunto<CMP>::conjunto_iterator conjunto<CMP>::upper_bound( const typename conjunto<CMP>::entrada &x ) const{
  typename conjunto<CMP>::const_iterator sal( upper_bound( vc.begin(), vc.end(), x, comp) );

  return sal;
}


template < class CMP >
conjunto<CMP>::iterator::iterator( const conjunto_iterator & it ){
	iter = it;
}


template < class CMP >
conjunto<CMP>::const_iterator::const_iterator( const conjunto_iterator & it ){
	iter = it;
}
