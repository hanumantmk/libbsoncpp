#ifndef BSONCPP_BSONC_UTILS_H
#define BSONCPP_BSONC_UTILS_H

#include "bson_bsonc.hpp"
#include <iostream>

namespace BSON {

class BSONCUtils {
public:
   static Value convert (const std::shared_ptr<BSONC::Impl> & impl, const bson_t * bson, const char * key);
   static Value convert (const std::shared_ptr<BSONC::Impl> & impl, const bson_iter_t * iter);
   static void pp (std::ostream & stream, bson_iter_t *iter, int indent, bool is_array);
   static void pp_type (std::ostream & stream, bson_iter_t *iter, int indent);
};

}

#endif
