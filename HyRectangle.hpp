#ifndef HYRECTANGLE_HPP
#define HYRECTANGLE_HPP

#include "HyBoundary.hpp"
#include "HyPoint.hpp"


template <typename T>
class HyRectangle : public HyBoundary<T>
{
protected:
  HyPoint<T>   aBL;
  HyPoint<T>   aUR;


public:
  HyRectangle();
  HyRectangle(HyPoint<T> & pBL, HyPoint<T> & pUR);
  
  HyPoint<T>  & getBL() {return aBL;}
  HyPoint<T>  & getUR() {return aUR;}
  void          setBL(HyPoint<T> & pBL) {aBL = pBL;}
  void          setUR(HyPoint<T> & pUR) {aUR = pUR;}
  
  double        getBoundary(HyPoint<T> & pPoint);
  double        getBoundary(T pX, T pY, T pZ);


};

template <typename T>
std::ostream & operator<<(std::ostream & pOut, HyRectangle<T> & pP);


#include "HyRectangle.ipp"

#endif
