#ifndef WOLRD_PARSER
#define WOLRD_PARSER

#include "world.h"

namespace tinyurdf
{
    template<typename T = double >
    class WorldParser
    {
    public:
        WorldParser();

        bool parse();

        urdf::World<T>* getWorld() const;
    private:

    }; 
}; // namespace tinyurdf
#endif  // WOLRD_PARSER