#include "link_parser.h"

namespace tinyurdf 
{
    template <typename T>
    LinkParser<T>::LinkParser()
    {
    }

    template <typename T>
    bool LinkParser<T>::parse()
    {
        return false;
    }

    template <typename T>
    urdf::Link<T> *LinkParser<T>::getLink() const
    {
      return nullptr;
    }
    
};// namespace tinyurdf 

template class tinyurdf::LinkParser<double>;
template class tinyurdf::LinkParser<float>;
template class tinyurdf::LinkParser<long double>;
