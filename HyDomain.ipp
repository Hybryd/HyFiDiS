#include "HyDomain.hpp"

template <typename T>
HyDomain<T>::HyDomain() : aBL(0,0,0), aUR(0,0,0)
{
}

template <typename T>
HyDomain<T>::HyDomain(const HyDomain & pDomain) : aBL(pDomain.aBL), aUR(pDomain.aUR)
{
}

template <typename T>
HyDomain<T>::HyDomain(HyPoint<T> pBL, HyPoint<T> pUR) : aBL(pBL), aUR(pUR)
{
}


template <typename T>
std::ostream & operator<<(std::ostream & out, HyDomain<T> pDomain)
{
  out << "HyDomain : " << pDomain.getBL() << " -> " << pDomain.getUR();
  return out;
}
