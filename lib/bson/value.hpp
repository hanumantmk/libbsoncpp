#ifndef BSONCPP_VALUE_H
#define BSONCPP_VALUE_H

#include <ostream>
#include <memory>
#include <iostream>
#include <tuple>

#include "bson/exception.hpp"

#define BSONCPP_VALUE_GUARD \
protected: \
   virtual void magicSizeGuard(Value v) const { \
      static_assert(sizeof(*this) <= Value::storage_size, "Type too large to fit in Value"); \
      static_assert(alignof(decltype(*this)) <= Value::storage_align, "Type too large to align in Value"); \
   }

namespace BSON {

class Value {
public:
   class Exception : BSON::Exception {
   public:
      Exception (const char *msg) : BSON::Exception (msg)
      {
      }
   };

   class Iterator;

   class Impl;
   static const size_t storage_size = 60;
   static const size_t storage_align = 8;

private:
   std::aligned_storage<storage_size, storage_align>::type storage;
   Impl *impl = NULL;
   Impl *clone_storage();

public:
   enum Type
   {
      Eod = 0x00,
      Double = 0x01,
      Utf8 = 0x02,
      Document = 0x03,
      Array = 0x04,
      Binary = 0x05,
      Undefined = 0x06,
      Oid = 0x07,
      Bool = 0x08,
      Date_time = 0x09,
      Null = 0x0A,
      Regex = 0x0B,
      Dbpointer = 0x0C,
      Code = 0x0D,
      Symbol = 0x0E,
      Codewscope = 0x0F,
      Int32 = 0x10,
      Timestamp = 0x11,
      Int64 = 0x12,
      Maxkey = 0x7F,
      Minkey = 0xFF,
   };

   Value ();
   ~Value ();

   Value( const Value& other);
   const Value& operator=( const Value& other);

   Value ( int32_t i);
   Value ( const char * s);
   Value ( const Value::Impl & i);

   Type get_type () const;

   bool has_value () const;
   explicit operator bool() const;

   const char * to_utf8() const;
   int32_t to_int32() const;
   std::tuple<const uint8_t *, size_t> to_bson() const;

   Value operator [] (const char * s) const;
   Value operator [] (int i) const;

   Iterator begin() const;
   Iterator end() const;

   void
   print (std::ostream & stream) const;
};

}

std::ostream & operator << (std::ostream & out, const BSON::Value &obj);

#endif
