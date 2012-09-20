///
/// \file 
/// \author Hybryd-
/// \date 2010
///
/// Header of HyPoint class
///

#ifndef HYPOINT_HPP
#define HYPOINT_HPP

/*           */
/* 3D point  */
/*           */

#include <cmath>
#include <iostream>
#include "Variables.hpp"

template <typename T>
class HyPoint
{
protected:
  T               aX;
  T               aY;
  T               aZ;
  unsigned long   aID;
  bool            aRegular;
  int             aLocality; // 1:inside the domain, 0:on the boundary, -1:outside the domain
  HyPoint *       aNeigW;
  HyPoint *       aNeigE;
  HyPoint *       aNeigN;
  HyPoint *       aNeigS;
  bool            aBoundary; // true if it is inside the domain but near the boundary
  
  
public:
  HyPoint();
  HyPoint(T pX, T pY, T pZ, unsigned long pID, bool pRegular);
  HyPoint(const HyPoint<T> & pP);
  
  T                 getX()                           const         {return aX;}
  T                 getY()                           const         {return aY;}
  T                 getZ()                           const         {return aZ;}
  unsigned long     getID()                          const         {return aID;}
  bool              getRegularity()                  const         {return aRegular;}
  int               getLocality()                    const         {return aLocality;}
  HyPoint *         getNeigW()                       const         {return aNeigW;}
  HyPoint *         getNeigE()                       const         {return aNeigE;}
  HyPoint *         getNeigN()                       const         {return aNeigN;}
  HyPoint *         getNeigS()                       const         {return aNeigS;}
  bool              getBoundary()                    const         {return aBoundary;}
  void              setX(T pX)                                {aX=pX;}
  void              setY(T pY)                                {aY=pY;}
  void              setZ(T pZ)                                {aZ=pZ;}
  void              setID(unsigned long int pID)              {aID=pID;}
  void              setRegularity(bool pRegular)              {aRegular=pRegular;}
  void              setLocality(int pLocality)                {aLocality=pLocality;}
  void              setNeigW(HyPoint * pNeig)                 {aNeigW = pNeig;}
  void              setNeigE(HyPoint * pNeig)                 {aNeigE = pNeig;}
  void              setNeigN(HyPoint * pNeig)                 {aNeigN = pNeig;}
  void              setNeigS(HyPoint * pNeig)                 {aNeigS = pNeig;}
  void              setBoundary(bool pBoundary)               {aBoundary = pBoundary;}
  
//  HyPoint<T> &      operator/(double pX);
//  HyPoint<T> &      operator+(const HyPoint<T> & pPoint);
  HyPoint<T> &      operator=(const HyPoint<T> & pPoint);
  bool              operator==(const HyPoint<T> & pPoint);
  bool              operator!=(const HyPoint<T> & pPoint);
  double            distance(const HyPoint<T> & pPoint);    // ||x||
  double            sqDistance(const HyPoint<T> & pPoint);  // ||x||²
  
};

template <typename T>
HyPoint<T> operator+(HyPoint<T> const& pA, HyPoint<T> const& pB);

template <typename T>
HyPoint<T> operator/(HyPoint<T> const& pA, double pX);



template <typename T>
std::ostream & operator<<(std::ostream & pOut, HyPoint<T> & pP);

#include "HyPoint.ipp"

#endif
