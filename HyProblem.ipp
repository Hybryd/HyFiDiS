/// \file   HyProblem.ipp
/// \brief  Template file of HyProblem class.



///
/// \fn HyProblem<T>::HyProblem()
/// \brief Default constructor
///


template <typename T>
HyProblem<T>::HyProblem()
{
}

///
/// \fn HyProblem<T>::HyProblem(HyBoundary2D<T> & pBoundary, std::string & pDescription, HyMesh2D<T> & pMesh)
/// \brief Constructor. Initializes the matrix and the vectors
/// \param pBoundary Boundary of the domain
/// \param pDescription Description of the problem
/// \param pMesh Mesh of the domain
///
template <typename T>
//HyProblem<T>::HyProblem(HyBoundary<T> & pBoundary,
//                        std::string & pDescription,
//                        HyMesh2D<T> & pMesh) : aMesh(pMesh),
//                                               aBoundary(pBoundary),
//                                               aDescription(pDescription),
//                                               aDomain(aBoundary.getDomain()),
//                                               aMatrix((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1)),
//                                               aX((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1),1.0),
//                                               aF((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1)),
//                                               aG((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1))
//{
//  //build();
//}
HyProblem<T>::HyProblem(HyDomain<T> & pDomain,
                        HyBoundary<T> & pBoundary,
                        HyMesh2D<T> & pMesh,
                        std::string & pDescription) :  aDomain(pDomain),
                                                aBoundary(pBoundary),
                                                aMesh(pMesh),
                                                aDescription(pDescription),
                                                aMatrix((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1),(aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1)),
                                                aX((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1)),
                                                aF((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1)),
                                                aG((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1))
{
  aMatrix.reserve(VectorXi::Constant((aMesh.getNbRectanglesX()+1)*(aMesh.getNbRectanglesY()+1),5)); // ===NOMBRE DE VOISINS CHANGE EN 3D
  for(unsigned long int i=0;i<aMatrix.innerSize();++i)
    aMatrix.coeffRef(i,i)=1;
  //build();
}



//template <typename T>
//std::ostream & operator<<(std::ostream & out, HyProblem<T> pProb)
//{
//  pProb.display(out);
//}


/////
///// \fn HyProblem<T>::applySolution()
///// \brief Set the Z coordinate of each point of the mesh to the corresponding value in the solution
/////
//template <typename T>
//void HyProblem<T>::applySolution()
//{
//  unsigned int lIndex;
//  for(unsigned int j=0;j<=aMesh.getNbRectanglesY();++j)
//  {
//    for(unsigned int i=0;i<=aMesh.getNbRectanglesX();++i)
//    {
//      lIndex=j*(aMesh.getNbRectanglesX()+1) + i;
//      
//      if(aMesh[i][j].getLocality()==1)
//        aMesh[i][j].setZ(aX(lIndex));
//      
//      if(aMesh[i][j].getBoundary())
//      {
//        aMesh[i][j].setZ(aG(lIndex));
////        std::cerr << aMesh[i][j] << " " << aG(lIndex) << std::endl;
//      }  
////        std::cerr << aMesh[i][j] << " " << aG(lIndex) << std::endl;
//    }
//  }
//}

///
/// \fn void HyProblem<T>::display(std::ostream & out)
/// \brief Displays the object HyProblem2D
///
template <typename T>
void HyProblem<T>::display(std::ostream & out)
{
  out << *this;
}


template <typename T>
void HyProblem<T>::displaySolutionGP(std::ostream & out)
{
//  std::cout << "DISPLAY" << std::endl;
  unsigned int lIndex;
  for(unsigned int j=0;j<=aMesh.getNbRectanglesY();++j)
  {
    for(unsigned int i=0;i<=aMesh.getNbRectanglesX();++i)
    {
      lIndex=j*(aMesh.getNbRectanglesX()+1) + i;
      #if DISPLAY_WHOLE_MESH == 0
        if (aMesh[i][j].getLocality() == 1)
          out << aMesh[i][j] << " " << aX[lIndex] << std::endl;
      #else
        out << aMesh[i][j] << " " << aX[lIndex] << std::endl;
      #endif
    }
  }
  out << std::endl;
}


///
/// \fn void HyProblem<T>::updateMesh()
/// \brief Check if each point is inside the domain Omega, on the boundary, or outside. Also update neighbourhood.
/// \param pPoint The point of evaluation
/// \return The value of the Dirichlet condition on pPoint
///

template <typename T>
void HyProblem<T>::updateMesh()
{
  unsigned long int lIndex = 0;
  double lBound = 0;
  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
  {
    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
    {
      
      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
      
//      std::cerr << "Point : (" << lIndex << ", " << this->aMesh[i][j].getLocality() << "," << this->aMesh[i][j].getBoundary() << ") : " << this->aMesh[i][j] << std::endl; 
      lBound = this->aBoundary.getBoundary(this->aMesh[i][j]);
      
      
      if(lBound > 0)
        this->aMesh[i][j].setLocality(1);
      else if (lBound == 0)
        this->aMesh[i][j].setLocality(0);
      else
        this->aMesh[i][j].setLocality(-1);
      
      if(j!=0)
        this->aMesh[i][j].setNeigS(&(this->aMesh[i][j-1]));
      if(j!=this->aMesh.getNbRectanglesY())
        this->aMesh[i][j].setNeigN(&(this->aMesh[i][j+1]));
      if(i!=0)
        this->aMesh[i][j].setNeigW(&(this->aMesh[i-1][j]));
      if(i!=this->aMesh.getNbRectanglesX())
        this->aMesh[i][j].setNeigE(&(this->aMesh[i+1][j]));
    }
  }  
}


///
/// \fn double HyProblem<T>::g(HyPoint<T> pPoint)
/// \brief The Dirichlet condition on the boundary
/// \param pPoint The point of evaluation
/// \return The value of the Dirichlet condition on pPoint
///
template <typename T>
double HyProblem<T>::g(HyPoint<T> pPoint)
{
	return g(pPoint.getX(),pPoint.getY(),pPoint.getZ());
}


///
/// \fn double HyProblem<T>::g(T pX, T pY)
/// \brief The Dirichlet condition on the boundary
/// \param pX, pY, pZ The coordinates of evaluation
/// \return The value of the Dirichlet condition on the point (pX,pY,pZ)
///
template <typename T>
double HyProblem<T>::g(T pX, T pY, T pZ)
{
  double res=0;
//  if(pX == 20 && pY >= 0 && pY <= 10)
//    res = 100;
//  else if(pX == 0 && pY >= 0 && pY <= 10)
//    res = 30;
//  else
//    res = 60;
//  res = pX + pY;
  
////  if(pY==0 && pX>=0 && pX <=20)
////    res = -50*sin(PI*pX/20);
////  if(pY==10 && pX>=0 && pX <=20)
////    res = -100*sin(PI*pX/10);
////    
////  if(pX==0 && pY>=0 && pY <=10)
////    res = 400*sin(PI*pY/10);
////  if(pX==20 && pY>=0 && pY <=10)
////    res = 100*sin(PI*pY/2.5);
  
	return res;
}


template <typename T>
HyProblem<T> & HyProblem<T>::operator=(const HyProblem<T> & pP)
{
  if(&pP != this)
  {
    aDomain = pP.getDomain();
    aBoundary = pP.getBoundary();
    aMesh = pP.getMesh();
    aDescription = pP.getDescription();
    aMatrix = pP.getMatrix();
    aX = pP.getX();
    aF = pP.getF();
    aG = pP.getG();
  }
  return *this;
}



///
/// \fn std::ostream & operator<<(std::ostream & out, HyProblem<T> pProb)
/// \brief Operator<<
///
template <typename T>
std::ostream & operator<<(std::ostream & out, HyProblem<T> pProb)
{
  out << "HyProblem   : " << pProb.getDescription() << std::endl;
  out << "Boundary    : " << pProb.getBoundary() << std::endl;
  out << "Domain      : " << pProb.getDomain() << std::endl;
  out << "Mesh        : ";
  if(pProb.getMesh().getNbRectanglesX()<=10 && pProb.getMesh().getNbRectanglesY()<=10)
    out << std::endl << pProb.getMesh() << std::endl;
  else
    out << " too big." << std::endl;
  out << "A      = ";
//  if(pProb.getMatrix().size() <= 26	)
    out << pProb.getMatrix() << std::endl;
//  else
//    out << " too big." << std::endl;
  
  out << "F           = " << pProb.getF() << std::endl;
  out << "G           = " << pProb.getG() << std::endl;
  out << "Solution    : " << pProb.getX() << std::endl;
  return out;
}

