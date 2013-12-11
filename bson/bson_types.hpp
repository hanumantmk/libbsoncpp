#ifndef BSONCPP_TYPES_H
#define BSONCPP_TYPES_H

#include <tuple>
#include "bson_value_impl.hpp"
#include <ostream>

namespace BSON {

template <Value::Type type>
class Type : public Value::Impl {
public:
   virtual ~Type() {}

   Value::Type get_type() const
   {
      return type;
   }
};

namespace Types {

class Null : Type<Value::Type::Null> {
public:
   void clone(Impl * storage) const {
      new (storage) Null();
   }

   void print (std::ostream &stream) const {
      stream << "NULL";
   }

   BSONCPP_VALUE_GUARD
};

class Int32 : Type<Value::Type::Int32> {
   int32_t val;
public:
   Int32(int32_t i) : val(i) {}

   void clone(Impl * storage) const {
      new (storage) Int32(val);
   }

   int32_t to_int32() const {
      return val;
   }

   void print (std::ostream &stream) const {
      stream << val;
   }

   BSONCPP_VALUE_GUARD
};

class Utf8 : Type<Value::Type::Utf8> {
   const char * val;

public:
   Utf8(const char * i) : val(i) {}

   void clone(Impl * storage) const {
      new (storage) Utf8(val);
   }

   const char * to_utf8() const {
      return val;
   }

   void print (std::ostream &stream) const {
      stream << val;
   }

   BSONCPP_VALUE_GUARD
};

}
}

#endif
