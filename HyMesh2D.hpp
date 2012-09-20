///
/// \file HyMesh2D.hpp
/// \date 2010
///
/// Header of HyMesh2D class. Represents a cartesian 2D mesh.
///

#ifndef HYMESH2D_HPP
#define HYMESH2D_HPP

#include <iostream>
#include <vector>
#include "HyMesh.hpp"
#include "Variables.hpp"



/*! \class HyMesh2D
* \brief Two dimensional mesh
*/

template <typename T>
class HyMesh2D : public HyMesh<T>
{
protected:
  std::vector< std::vector<HyPoint<T> > > aMesh;          /*!< The mesh */
  unsigned long                           aNbRectanglesX; /*!< Number of nodes on X-axis */
  unsigned long                           aNbRectanglesY; /*!< Number of nodes on Y-axis */
  double                                  ahX;            /*!< Size between two nodes on X-axis */
  double                                  ahY;            /*!< Size between two nodes on Y-axis */

public:
  /*!
  * \brief Default constructor
  */
  HyMesh2D();
  
  /*!
  *  \brief Constructor
  *  \param pBL : The Bottom Left point
  *  \param pUR : The Upper Right point
  *  \param pNbRectanglesX : Number of nodes on X-axis
  *  \param pNbRectanglesY : Number of nodes on Y-axis
  */
  HyMesh2D(HyPoint<T> & pBL, HyPoint<T> & pUR, unsigned long pNbRectanglesX, unsigned long pNbRectanglesY);
  
  
  /*!
  *  \brief Copy constructor
  *  \param pMesh : Reference to another HyMesh
  */  
  HyMesh2D( HyMesh2D<T> & pMesh);

  /*!
  *  \brief Getter to aMesh attribute
  *  \return Reference to aMesh
  */
  std::vector< std::vector< HyPoint<T> > > & getMesh() {return aMesh;          }
  
  /*!
  *  \brief Getter to aNbRectanglesX attribute
  *  \return aNbRectanglesX
  */
  unsigned long getNbRectanglesX()                     {return aNbRectanglesX; }
  
  /*!
  *  \brief Getter to aNbRectanglesY attribute
  *  \return aNbRectanglesY
  */
  unsigned long getNbRectanglesY()                     {return aNbRectanglesY; }
  
  /*!
  *  \brief Getter to ahX attribute
  *  \return ahX
  */
  double        getHX()                                {return ahX;            }
  
  /*!
  *  \brief Getter to ahY attribute
  *  \return ahY
  */
  double        getHY()                                {return ahY;            }
  
  /*!
  *  \brief Number of points in the mesh
  *  \return The number of points in the mesh
  */
  unsigned long size()                                 {return aMesh.size()*aMesh[0].size();  }
  
  /*!
  *  \brief operator[]
  */
  std::vector< HyPoint<T> > & operator[](unsigned long i);
  void  display() {std::cout << "";}
};


/*!
*  \brief operator<<
*/
template <typename T>
std::ostream & operator<<(std::ostream & out, HyMesh2D<T> & pM);

#include "HyMesh2D.ipp"

#endif


