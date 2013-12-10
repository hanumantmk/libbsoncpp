#ifndef BSONCPP_BSONC_DOC_H
#define BSONCPP_BSONC_DOC_H

#include "bson_bsonc_type.hpp"

namespace BSON {

class BSONC::Types::Doc : public BSONC::Type<Value::Type::Document> {
private:
   bson_uint32_t len;
   const bson_uint8_t *buf;

public:
   Doc (const std::shared_ptr<BSONC::Impl> &i, const bson_uint8_t *buf, bson_uint32_t len);

   void clone(Value::Impl * storage) const;

   Value operator [] (const char * s) const;

   void print (std::ostream & stream) const;

   BSONCPP_VALUE_GUARD(BSONC::Types::Doc)
};

}

#endif
