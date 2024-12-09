#include "color.h"

namespace urdf
{
    template <typename T>
    Color<T>::Color()
    {
        r = g = b = static_cast<T>(0.0);
        a = static_cast<T>(1.0);
    }

    template <typename T>
    Color<T>::Color(const T& r_,const T& g_,const T& b_,const T& a_)
    {
        if (r_ < static_cast<T>(0.0) || r_ > static_cast<T>(1.0) ||
            g_ < static_cast<T>(0.0) || g_ > static_cast<T>(1.0) ||
            b_ < static_cast<T>(0.0) || b_ > static_cast<T>(1.0) ||
            a_ < static_cast<T>(0.0) || a_ > static_cast<T>(1.0))
        {
            LOG_F(ERROR, "RGBA values must be in the range [0.0, 1.0]. Received: r=%f, g=%f, b=%f, a=%f", 
                static_cast<double>(r_), static_cast<double>(g_), 
                static_cast<double>(b_), static_cast<double>(a_));
            throw std::invalid_argument("RGBA values out of range [0.0, 1.0]");
        }
        r = r_; g = g_; b = b_; a = a_;
    }

    template <typename T>
    void Color<T>::clear()
    {
        r = g = b = static_cast<T>(0.0);
        a = static_cast<T>(1.0);
    }

    template <typename T>
    Color<T>::Color(const std::string &vector_str)
    {
        clear();
        std::vector<std::string> pieces;
        std::vector<T>       rgba;
        std::istringstream stream(vector_str);
        std::string piece;
        while (stream >> piece) {
        
            rgba.push_back(std::atof(piece.c_str()));
        }
        if (rgba.size() != 4)
        {
            LOG_F(ERROR, "Color contains %i elements instead of 4 elements", (int)rgba.size());
        }
        this->r = rgba[0];
        this->g = rgba[1];
        this->b = rgba[2];
        this->a = rgba[3];
    }
    template <typename T>
    std::string Color<T>::str()
    {
        return std::string();
    }
}; // namespace urdf

template class urdf::Color<double>;
template class urdf::Color<long double>;
template class urdf::Color<float>;