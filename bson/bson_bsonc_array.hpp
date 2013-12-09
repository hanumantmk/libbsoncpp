#ifndef BSONCPP_BSONC_ARRAY_H
#define BSONCPP_BSONC_ARRAY_H

#include "bson_bsonc_type.hpp"

namespace BSON {

class BSONC::Type::Array : public BSONC::Type {
private:
   bson_uint32_t len;
   const bson_uint8_t *buf;

public:
   Array (const std::shared_ptr<BSONC::Impl> &i, const bson_uint8_t *buf, bson_uint32_t len);

   void clone(Value::Impl * storage) const;

   Value operator [] (int i) const;

   void print (std::ostream & stream) const;

   BSONCPP_VALUE_GUARD(BSONC::Type::Array)
};

}

#endif
