/*!
*
* \file   HyPlotter.ipp
* \brief  Template file of HyPlotter class.
*
*/


/*!
*
* \fn HyPlotter<T>::HyPlotter()
* \brief Default constructor of HyPlotter.
*
*/
template <typename T>
HyPlotter<T>::HyPlotter()
{

}

/*!
*
* \fn HyPlotter<T>::HyPlotter(std::string pDescription)
* \brief Constructor of HyPlotter.
* \param pMesh The mesh corresponding to the problem.
* \param pData The solution.
* \param pFileName The name of the output file.
*
*/


template <typename T>
HyPlotter<T>::HyPlotter(HyMesh2D<T> pMesh, std::vector<Eigen::VectorXd> pData, std::string pFileName) : aMesh(pMesh), aFileName(pFileName)
{
  for(unsigned long int i=0;i<pData.size();++i)
  {
    aData.push_back(pData[i]);
  }
}

/*!
*
* \fn std::string  HyPlotter<T>::intToString(unsigned long int n)
* \brief Converts an integer to a string.
* \param n The integer to convert to string.
*
*/

template <typename T>
std::string  HyPlotter<T>::intToString(unsigned long int n)
{
	std::stringstream ss;
	ss << n;
	return ss.str();
}

/*!
*
* \fn void HyPlotter<T>::save(std::string pFolder)
* \brief Save the data in files. In case of a time dependent solution (several VectorXd), suffixes will be written for the name of the files.
* \param pFolder The folder to save files in.
*
*/

template <typename T>
void HyPlotter<T>::save(std::string pFolder)
{
  std::string prefix=""; // No more than 9999 steps
  
  for(unsigned long int t=0;t<aData.size();++t)
  {
    if(t < 10)
      prefix="000";
    else if (t<100)
      prefix = "00";
    else if (t<1000)
      prefix = "0";
    else if (t<10000)
      prefix = "";
    else
      std::cerr << "WARNING in void HyPlotter<T>::save(std::string pFolder) : number of files exceeds 10000." << std::endl;
      
    std::fstream output((pFolder + "/" +  aFileName + prefix + intToString(t)).c_str(),std::ios::out);
    if(output)
    {
      unsigned int lIndex=0;
      for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
      {
        for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
        {
          lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
          #if DISPLAY_WHOLE_MESH == 0
            if (this->aMesh[i][j].getLocality() == 1)
              output << this->aMesh[i][j] << " " << this->aData[t](lIndex) << std::endl;
          #else
            output << this->aMesh[i][j] << " " << this->aData[t](lIndex) << std::endl;
          #endif
        }
      }
      output << std::endl;
      output.close();
    }
    else
      std::cerr << "ERROR in void HyPlotter<T>::save(std::string pFolder) : unable to open " << (pFolder + "/" + aFileName + prefix + intToString(t)) << std::endl;
  }
}





