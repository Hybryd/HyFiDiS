#ifndef HYCIRCLE_HPP
#define HYCIRCLE_HPP

/*!
*
* \file   HyCircle.hpp
* \brief  Header file of HyCircle class.
*
*/

#include "HyBoundary.hpp"
#include "HyPoint.hpp"


template <typename T>
class HyCircle : public HyBoundary<T>
{
protected:
  double        aRadius;
  HyPoint<T>    aCenter;


public:
  HyCircle();
  HyCircle(double pRadius, HyPoint<T> & pP);
  
  double        getRadius() {return aRadius;}
  HyPoint<T>  & getCenter() {return aCenter;}
  void          setRadius(double pRadius) {aRadius = pRadius;}
  void          setCenter(HyPoint<T> & pCenter) {aCenter = pCenter;}
  
  double        getBoundary(HyPoint<T> & pPoint);
  double        getBoundary(T pX, T pY, T pZ);

  HyCircle<T> &      operator=(const HyCircle<T> & pC);


};

template <typename T>
std::ostream & operator<<(std::ostream & pOut, HyCircle<T> & pP);


#include "HyCircle.ipp"

#endif
