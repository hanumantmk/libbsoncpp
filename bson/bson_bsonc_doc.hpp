#ifndef BSONCPP_BSONC_DOC_H
#define BSONCPP_BSONC_DOC_H

#include "bson_bsonc_type.hpp"

namespace BSON {

class BSONC::Type::Doc : public BSONC::Type {
private:
   class Check;
   bson_uint32_t len;
   const bson_uint8_t *buf;

public:
   Doc (const std::shared_ptr<bson_t> &i, const bson_uint8_t *buf, bson_uint32_t len);

   void clone(Impl * storage) const;

   Value operator [] (const char * s) const;

   void print (std::ostream & stream) const;

   BSONCPP_VALUE_GUARD(BSONC::Type::Doc)
};

}

#endif
