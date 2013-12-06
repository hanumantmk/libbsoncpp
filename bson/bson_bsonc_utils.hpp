#ifndef BSONCPP_BSONC_UTILS_H
#define BSONCPP_BSONC_UTILS_H

#include "bson_bsonc.hpp"

namespace BSON {

class BSONCUtils {
public:
   static Value convert (const std::shared_ptr<bson_t> & root, const bson_t * bson, const std::string & s);
};

}

#endif
