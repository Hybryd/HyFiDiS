#ifndef HYPLOTTER_HPP
#define HYPLOTTER_HPP


/*!
* \file   HyPlotter.hpp
* \brief  Header file of HyPlotter class.
*
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>

#include "HyMesh2D.hpp"

/*!
*
* \class HyPlotter
* \brief This class is used for post-processing analysis. Given a HyMesh and a set of data, it saves the solution in a file.
*
*/

template <typename T>
class HyPlotter
{
protected:
  /*! The mesh */
  HyMesh2D<T>                     aMesh;
  /*! The values corresponding to each point of the mesh */
  std::vector<Eigen::VectorXd>    aData;
  /*! The name of the file to save in */
  std::string                     aFileName;

public:
  HyPlotter();
  HyPlotter(HyMesh2D<T> pMesh, std::vector<Eigen::VectorXd> pData, std::string pFileName);
  
  std::string intToString(unsigned long int n);
  
  void save(std::string pFolder);


};


#include "HyPlotter.ipp"

#endif
