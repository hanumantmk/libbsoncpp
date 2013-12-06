#ifndef BSONCPP_EXCEPTION_H
#define BSONCPP_EXCEPTION_H

#include <stdexcept>

namespace BSON {

class Exception: public std::runtime_error {
public:
   Exception(const char * msg) : std::runtime_error(msg) {}
};

}

#endif
