#ifndef __CONJUTO_H
#define __CONJUTO_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "crimen.h"

using namespace std;

template < class CMP >
class conjunto{
private:
  vector<crimen> vc;
  CMP comp;

public:
  typedef crimen entrada ;
  typedef unsigned int size_type;
  typedef vector<crimen>::iterator conjunto_iterator;
  typedef vector<crimen>::const_iterator conjunto_const_iterator;

  conjunto();
  conjunto(const conjunto<CMP> & d);
  conjunto( vector<conjunto<CMP>::entrada> & v_entrada );
  size_type size() const;

  class iterator{
  private:
    friend class conjunto;
    conjunto_iterator iter;

    // Constructores para begin() y end().
    iterator( const conjunto_iterator & it );

  };

  class const_iterator{
  private:
    friend class conjunto;
    conjunto_const_iterator iter;

    const_iterator( const conjunto_iterator &it );

  };

  typename conjunto<CMP>::iterator lower_bound( const typename conjunto<CMP>::entrada &x );
  typename conjunto<CMP>::const_iterator lower_bound( const typename conjunto<CMP>::entrada &x ) const;
  typename conjunto<CMP>::iterator upper_bound( const typename conjunto<CMP>::entrada &x );
  typename conjunto<CMP>::conjunto_iterator upper_bound( const typename conjunto<CMP>::entrada &x ) const;
};

#include "conjunto.hxx"
#endif
