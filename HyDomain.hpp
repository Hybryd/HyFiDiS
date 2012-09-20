#ifndef HYDOMAIN_HPP
#define HYDOMAIN_HPP

#include "HyPoint.hpp"

template <typename T>
class HyDomain
{
protected:
  HyPoint<T> aBL; // Bottom-Left
  HyPoint<T> aUR; // Upper-Right
public:
  HyDomain();
  HyDomain(const HyDomain & pDomain);
  HyDomain(HyPoint<T> pBL, HyPoint<T> pUR);
  
  HyPoint<T> & getBL() {return aBL;}
  HyPoint<T> & getUR() {return aUR;}
  
};

template <typename T>
std::ostream & operator<<(std::ostream & out, HyDomain<T> pDomain);

#include "HyDomain.ipp"

#endif
