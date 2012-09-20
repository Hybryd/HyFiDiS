#ifndef _HYMESH_HPP
#define _HYMESH_HPP

/*                                    */
/* Cartesian mesh of a cubic domain   */
/* defined by its bottom-left and     */
/* upper-right points                 */

#include <iostream>
#include <vector>

#include "HyPoint.hpp"

template <typename T>
class HyMesh
{
protected:
  unsigned int        aDimension;

public:
  HyMesh();
  
  unsigned int        getDimension()  {return aDimension;}
  virtual void        display()=0;
};

#include "HyMesh.ipp"

#endif
