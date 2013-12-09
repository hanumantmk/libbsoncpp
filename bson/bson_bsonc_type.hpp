#ifndef BSONCPP_BSONC_Type_H
#define BSONCPP_BSONC_Type_H

#include "bson_bsonc.hpp"
#include "bson_value_impl.hpp"

namespace BSON {

class BSONC::Type : public Value::Impl {
public:
   class UTF8;
   class Doc;
   class Array;

private:
   std::shared_ptr<BSONC::Impl> impl;

public:
   Type (Value::Type t, const std::shared_ptr<BSONC::Impl> &b);

   virtual ~Type() {};
};


}

#endif
