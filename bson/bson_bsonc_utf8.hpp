#ifndef BSONCPP_BSONC_UTF8_H
#define BSONCPP_BSONC_UTF8_H

#include "bson_bsonc_type.hpp"

namespace BSON {

class BSONC::Types::UTF8 : public BSONC::Type<Value::Type::UTF8> {
private:
   const char *val;

public:
   UTF8 (const std::shared_ptr<BSONC::Impl> &b, const char *v);

   void clone(Value::Impl * storage) const;

   const char * to_utf8() const;

   void print (std::ostream & stream) const;

   BSONCPP_VALUE_GUARD(BSONC::Types::UTF8)
};

}

#endif
