/// \file   HyStokes2D.ipp
/// \brief  Template file of HyStokes2D class.

///
/// \fn HyStokes2D<T>::HyStokes2D()
/// \brief Default constructor
///
template <typename T>
HyStokes2D<T>::HyStokes2D()
{
}


///
/// \fn HyStokes2D<T>::HyStokes2D(HyBoundary2D<T> & pBoundary, std::string & pDescription, HyMesh2D<T> & pMesh)
/// \brief Constructor. Initializes the matrix and the vectors
/// \param pBoundary Boundary of the domain
/// \param pDescription Description of the problem
/// \param pMesh Mesh of the domain
///
template <typename T>
HyStokes2D<T>::HyStokes2D(  HyDomain<T> & pDomain,
                              HyBoundary<T> & pBoundary,
                              HyMesh2D<T> & pMesh,
                              std::string & pDescription
                           ) : HyProblem<T>(pDomain,pBoundary,pMesh,pDescription)
{
  unsigned int lNbX = this->aMesh.getNbRectanglesX()+1;
  unsigned int lNbY = this->aMesh.getNbRectanglesY()+1;
  
  /*
    The theoretical linear system is:
    
    |A  B| |X| |F|
    |B' 0|.|P|=|0|
    
    
                      |A  B|
    aMatrix         : |B' 0|    (2 * lNbX * lNbY) * (2 * lNbX * lNbY)
    aMatrixA        : A         (lNbX * lNbY) * (lNbX * lNbY)
    aMatrixB        : B         (lNbX * lNbY) * (lNbX * lNbY)
    aX              : X         (2 * lNbX * lNbY)
    aP              : P         (lNbX * lNbY)
    aF              : F         (2 * lNbX * lNbY)
  
    The linear system that will be computed is:
  
    |A    B| |X| |F|
    |B' -eI|.|P|=|0|
    
    where e is epsilon, taken as little as wanted.
  */
  
  this->aMatrix(2*lNbX*lNbY,2*lNbX*lNbY);
  this->aMatrixA(lNbX*lNbY,lNbX*lNbY);
  this->aMatrixB(lNbX*lNbY,lNbX*lNbY);
  this->aX(2*lNbX*lNbY);
  this->aF(2*lNbX*lNbY);
  this->aG(2*lNbX*lNbY);
  this->aMatrix.reserve(VectorXi::Constant(lNbX*lNbY,5 + 2)); // ===NOMBRE DE VOISINS CHANGE EN 3D
  this->aMatrixA.reserve(VectorXi::Constant(lNbX*lNbY,5));
  this->aMatrixB.reserve(VectorXi::Constant(lNbX*lNbY,2));
  for(unsigned long int i=0;i<this->aMatrix.innerSize();++i)
    this->aMatrix.coeffRef(i,i)=1;
  build();
}



///
/// \fn void HyStokes2D<T>::build()
/// \brief Fills the matrix A and the vectors F and G
///
template <typename T>
void HyStokes2D<T>::build()
{

  unsigned long int lIndex = 0;
  unsigned long int lNeigW, lNeigE, lNeigN, lNeigS;
  double            lBound;
  bool              lIsOnBoundary=false;
  

  HyProblem<T>::updateMesh();
  
  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
  {
    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
    {
      lNeigW = 0;
      lNeigE = 0;
      lNeigN = 0;
      lNeigS = 0;


      // Index of the Xij in the matrix and vector
      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
      
      // Set if the point is in the domain omega and has at least one neigbour outside
      lIsOnBoundary=false;
      if(this->aMesh[i][j].getLocality()==-1)
      {
        this->aMesh[i][j].setBoundary(false);
      }
      else if(this->aMesh[i][j].getLocality()==1)
      {
        if(this->aMesh[i][j].getNeigW() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigW()->getLocality() == -1);
        if(this->aMesh[i][j].getNeigE() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigE()->getLocality() == -1);
        if(this->aMesh[i][j].getNeigN() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigN()->getLocality() == -1);
        if(this->aMesh[i][j].getNeigS() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigS()->getLocality() == -1);
        this->aMesh[i][j].setBoundary(lIsOnBoundary);
//        std::cout << this->aMesh[i][j] << " : " << this->aMesh[i][j].getBoundary() << std::endl;
      }
      else if(this->aMesh[i][j].getLocality()==0)
        this->aMesh[i][j].setBoundary(true);
        
        
        
        
      
      
      
    }
  }
  
  
}

