#ifndef BSONCPP_VALUE_H
#define BSONCPP_VALUE_H

#include <ostream>
#include <memory>
#include <iostream>

#define BSONCPP_VALUE_GUARD(name) \
protected: \
   void magicSizeGuard() const { \
      static_assert(sizeof(name) <= Value::storage_size, "Type too large to fit in Value"); \
      static_assert(alignof(name) <= Value::storage_align, "Type too large to align in Value"); \
   }

namespace BSON {

class Value {
public:
   class Impl;
   static const size_t storage_size = 50;
   static const size_t storage_align = 8;

private:
   std::aligned_storage<storage_size>::type storage;
   Impl *impl;

public:
   enum Type
   {
      Root,
      Document,
      Array,
      Null,
      UTF8,
   };

   Value ();
   ~Value ();

   Value( const Value& other);
   const Value& operator=( const Value& other);

   Impl *
   get_impl();

   Type get_type () const;

   void
   print (std::ostream & stream) const;
};

}

std::ostream & operator << (std::ostream & out, const BSON::Value &obj);

#endif
