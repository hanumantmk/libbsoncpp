#ifndef BSONCPP_TYPES_H
#define BSONCPP_TYPES_H

#include <tuple>
#include <array>
#include "bson/value_impl.hpp"
#include "bson/value.hpp"
#include <ostream>

namespace BSON {

class Type : public ValueImpl
{
   ValueType type;

   union Storage {
      const char * utf8;
      int32_t int32;
      struct {
         const uint8_t *buf;
         size_t len;
      } bson;
   } u;

   Type(ValueType t, Storage & s) : type(t), u(s) {}

public:
   Type(const Type & t) : type(t.type), u(t.u) {}

   static Type Int32(int32_t i) {
      Storage u;
      u.int32 = i;
      return Type(ValueType::Int32, u);
   }

   static Type Utf8(const char * utf8) {
      Storage u;
      u.utf8 = utf8;
      return Type(ValueType::Utf8, u);
   }

   static Type Document(const uint8_t *buf, size_t len) {
      Storage u;
      u.bson.buf = buf;
      u.bson.len = len;
      return Type(ValueType::Document, u);
   }

   static Type Array(const uint8_t *buf, size_t len) {
      Storage u;
      u.bson.buf = buf;
      u.bson.len = len;
      return Type(ValueType::Array, u);
   }

   static Type Null() {
      Storage u;
      return Type(ValueType::Null, u);
   }

   ValueType get_type() const
   {
      return type;
   }

   auto clone(ValueImpl * storage) const -> ValueImpl *
   {
      return new (storage) Type(*this);
   }

   const char * to_utf8() const {
      return u.utf8;
   }

   int32_t to_int32() const {
      return u.int32;
   }

   std::tuple<const uint8_t *, size_t> to_bson() const
   {
      return std::make_tuple(u.bson.buf, u.bson.len);
   }

   void print (std::ostream & stream) const
   {
      switch (get_type()) {
         case ValueType::Int32:
            stream << to_int32();
            break;
         case ValueType::Utf8:
            stream << to_utf8();
            break;
         default:
            stream << "?";
            break;
      }
   }

   BSONCPP_VALUE_GUARD;
};

namespace Types {
   Type Int32(int32_t i);

   Type Utf8(const char * utf8);

   Type Null();

   Type Array(const uint8_t *buf, size_t len);

   Type Document(const uint8_t *buf, size_t len);
}

}

#endif
