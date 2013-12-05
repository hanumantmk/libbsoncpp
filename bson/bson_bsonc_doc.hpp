#ifndef BSONCPP_BSONC_DOC_H
#define BSONCPP_BSONC_DOC_H

#include "bson_bsonc_type.hpp"

namespace BSON {

class BSONC::Type::Doc : public BSONC::Type {
private:
   bson_t child;

public:
   Doc (const std::shared_ptr<bson_t> &i, bson_iter_t * t);

   void print (std::ostream & stream) const;
};

}

#endif
