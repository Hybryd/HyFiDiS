#include "HySolver.hpp"

template <typename T>
HySolver<T>::HySolver() : aError(0)
{
}


template <typename T>
void HySolver<T>::withBiCGSTAB(HyProblem<T> & pProblem)
{
//  std::cerr << pProblem.getMatrix() << std::endl;
  #if QUIET == 0
    std::cout << "Solving using BiCGSTAB method...";
  #endif
  BiCGSTAB<SparseMatrix<T> > solver(pProblem.getMatrix());
  pProblem.setX(solver.solve(pProblem.getF() + pProblem.getG()));
  #if QUIET == 0
    switch (solver.info())
    {
      case 0:
        std::cout << " OK." << std::endl;
        std::cout << " Number of iterations: " << solver.iterations() << std::endl;
        std::cout << " Estimated error:      " << solver.error()      << std::endl;
      break;
      
      case 1:
        std::cout << " ERROR: The provided data did not satisfy the prerequisites." << std::endl;
      break;
      
      case 2:
        std::cout << " ERROR: Iterative procedure did not converge." << std::endl;
      break;
      
      case 3:
        std::cout << " ERROR: The inputs are invalid, or the algorithm has been improperly called. When assertions are enabled, such errors trigger an assert." << std::endl;
      break;
    
    }
    
  #endif
}



template <typename T>
void HySolver<T>::withConjugateGradient(HyProblem<T> & pProblem)
{

}









//// Homemade Gauss_Seidel solver
//// Does not check if the Matrix is such as aii != 0
//template <typename T>
//void HySolver<T>::Gauss_Seidel(HyMatrix<T> pA, HyVector<T> & pXk, HyVector<T> & pB, unsigned int kMax)
//{
//  HyVector<T> lXk1 = pXk;
//  unsigned int lSize = pXk.size();
//  double lSom1=0;
//  double lSom2=0;
//  for(unsigned int k=0; k<kMax; ++k)
//  {
//    for(unsigned int i=0; i<lSize; ++i)
//    {
//      lSom1=0;
//      lSom2=0;
//      for(unsigned int j=0; j<i; ++j)
//      {
//        lSom1+= pA[i][j]*lXk1[j];
//      }
//      for(unsigned int j=i+1; j<lSize; ++j)
//      {
//        lSom2+= pA[i][j]*pXk[j];
//      }
//      
//      lXk1[i] = (pB[i]-lSom1-lSom2)/(pA[i][i]);
//    }
//    pXk = lXk1;
//  }
//}


//template <typename T>
//void HySolver<T>::Gauss_Seidel(HyProblem<T> & pProblem)
//{
//  HyVector<T> lFG(pProblem.getF() + pProblem.getG()); // Changer vecteur F+G = vecteur FG
//  Gauss_Seidel(pProblem.getMatrix(), pProblem.getX(), lFG, 4); // changer 4
//}

