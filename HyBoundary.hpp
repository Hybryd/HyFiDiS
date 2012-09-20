#ifndef HYBOUNDARY_HPP
#define HYBOUNDARY_HPP

/*!
*
* \file   HyBoundary.hpp
* \brief  Header file of HyBoundary class.
*
*/

#include <string>
#include "HyDomain.hpp"
#include "HyPoint.hpp"

/*!
*
* \class HyBoundary
* \brief Define the border of the domain for a given problem. It is represented by a function, defined in the whole space, which value is positive inside the domain, 0 exactly on the boundary, and negative outside. This class is virtual.
*
*/

template <typename T>
class HyBoundary
{
protected:
  /*! A brief description of the boundary */
  std::string   aDescription;
  
public:
  HyBoundary();
  HyBoundary(std::string pDescription);//, HyDomain<T> pDomain);
  
  
  std::string       getDescription() const {return aDescription;}
  double            getBoundary(HyPoint<T> & pPoint);
  virtual double    getBoundary(T pX, T pY, T pZ) = 0;
  
  HyBoundary<T> &      operator=(const HyBoundary<T> & pB);
  
};

template <typename T>
std::ostream & operator<<(std::ostream & out, HyBoundary<T> pBound);

#include "HyBoundary.ipp"

#endif
