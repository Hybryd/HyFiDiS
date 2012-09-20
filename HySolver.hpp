#ifndef HYSOLVER_HPP
#define HYSOLVER_HPP

#include <iostream>


//#include <Eigen/SparseCholesky>
#include <Eigen/IterativeLinearSolvers>

#include "Variables.hpp"
#include "HyProblem.hpp"



template <typename T>
class HySolver
{
protected:
  double        aError;
 
public:
  HySolver();
  
  void withBiCGSTAB(HyProblem<T> & pProblem);
  void withConjugateGradient(HyProblem<T> & pProblem);
  
//  void Gauss_Seidel(HyMatrix<T> pA, HyVector<T> & pXk, HyVector<T> & pB, unsigned int kMax);
//  void Gauss_Seidel(HyProblem<T> & pProblem); // changer UML

};

#include "HySolver.ipp"

#endif
