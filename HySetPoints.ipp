
template <typename T>
HySetPoints<T>::HySetPoints()
{
}

template <typename T>
void HySetPoints<T>::add(HyPoint<T> * pPoint)
{
  aSet.push_back(pPoint);
}

template <typename T>
void HySetPoints<T>::add(HyPoint<T> & pPoint)
{
  aSet.push_back(&pPoint);
}

template <typename T>
HyPoint<T> & HySetPoints<T>::operator[] (unsigned int i)
{
  if(i>=0 && i<aSet.size())
    return *(aSet[i]);
  else
    std::cerr << "ERROR in HySetPoints<T>::operator[] (unsigned int i) : " << std::endl;
    std::cerr << "   Check the index" << std::endl;
}

template <typename T>
std::ostream & operator<<(std::ostream & out, HySetPoints<T> & pSet)
{
  for(unsigned int i=0;i<pSet.size();++i)
  {
    out << pSet[i] << std::endl;
  }
  return out;
}

