#ifndef BSONCPP_BSONC_Type_H
#define BSONCPP_BSONC_Type_H

#include "bson_bsonc.hpp"
#include "bson_value_impl.hpp"

namespace BSON {

template <Value::Type t>
class BSONC::Type : public Value::Impl {
protected:
   std::shared_ptr<BSONC::Impl> impl;

public:
   Type (const std::shared_ptr<BSONC::Impl> &b) :
      impl(b)
   {
   }

   Value::Type get_type() const {
      return t;
   }

   virtual ~Type() {};
};


}

#endif
