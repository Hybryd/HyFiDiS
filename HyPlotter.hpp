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


template <typename T>
class HyPlotter
{
protected:
  HyMesh2D<T>                     aMesh;
  std::vector<Eigen::VectorXd>    aData;
  std::string                     aFileName;

public:
  HyPlotter();
  HyPlotter(HyMesh2D<T> pMesh, std::vector<Eigen::VectorXd> pData, std::string pFileName);
  
  std::string intToString(unsigned long int n);
  
  void save(std::string pFolder);


};


#include "HyPlotter.ipp"

#endif
