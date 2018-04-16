/**
* Functor para la práctica AVL.
* Alberto Armijo Ruiz.
* 2º GII A.
*/

#ifndef __COMPARE_H
#define __COMPARE_H
template <typename T>

class compare{
  public:
    bool operator()(const T & a, const T & b)const;
};

#include "functor.hxx"

#endif
