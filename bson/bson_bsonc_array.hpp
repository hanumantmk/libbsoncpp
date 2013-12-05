#ifndef BSONCPP_BSONC_ARRAY_H
#define BSONCPP_BSONC_ARRAY_H

#include "bson_bsonc_type.hpp"

namespace BSON {

class BSONC::Type::Array : public BSONC::Type {
private:
   bson_t child;

public:
   Array (const std::shared_ptr<bson_t> &i, bson_iter_t * t);

   void print (std::ostream & stream) const;
};

}

#endif
