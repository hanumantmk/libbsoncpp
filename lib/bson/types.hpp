#ifndef BSONCPP_TYPES_H
#define BSONCPP_TYPES_H

#include <tuple>
#include <array>
#include "bson/value_impl.hpp"
#include <ostream>

namespace BSON {

class Type : public Value::Impl
{
   Value::Type type;

   union Storage {
      const char * utf8;
      int32_t int32;
      struct {
         const uint8_t *buf;
         size_t len;
      } bson;
   } u;

   Type(Value::Type t, Storage & s) : type(t), u(s) {}

public:
   Type(const Type & t) : type(t.type), u(t.u) {}

   static Type Int32(int32_t i) {
      Storage u;
      u.int32 = i;
      return Type(Value::Type::Int32, u);
   }

   static Type Utf8(const char * utf8) {
      Storage u;
      u.utf8 = utf8;
      return Type(Value::Type::Utf8, u);
   }

   static Type Document(const uint8_t *buf, size_t len) {
      Storage u;
      u.bson.buf = buf;
      u.bson.len = len;
      return Type(Value::Type::Document, u);
   }

   static Type Array(const uint8_t *buf, size_t len) {
      Storage u;
      u.bson.buf = buf;
      u.bson.len = len;
      return Type(Value::Type::Array, u);
   }

   static Type Null() {
      Storage u;
      return Type(Value::Type::Null, u);
   }

   Value::Type get_type() const
   {
      return type;
   }

   auto clone(Impl * storage) const -> Impl *
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
         case Value::Type::Int32:
            stream << to_int32();
            break;
         case Value::Type::Utf8:
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
