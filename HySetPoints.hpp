#ifndef HYSETPOINTS_HPP
#define HYSETPOINTS_HPP


/*                                    */
/* Vector of already allocated points */
/*                                    */

#include <iostream>
#include "HyPoint.hpp"

template <typename T>
class HySetPoints
{
protected:
  std::vector< HyPoint<T> * > aSet;

public:
  HySetPoints();
  
  std::vector< HyPoint<T> * > & getSet() {return aSet;}
  unsigned int size() {return aSet.size();}
  HyPoint<T> & operator[] (unsigned int i);
  
  
  void add(HyPoint<T> * pPoint);
  void add(HyPoint<T> & pPoint);
  
};

template <typename T>
std::ostream & operator<<(std::ostream & out, HySetPoints<T> & pSet);

#include "HySetPoints.ipp"

#endif
