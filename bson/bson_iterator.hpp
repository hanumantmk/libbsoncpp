#ifndef BSONCPP_VALUE_ITERATOR_H
#define BSONCPP_VALUE_ITERATOR_H

#include "bson_value.hpp"

#define BSONCPP_VALUE_ITERATOR_GUARD \
protected: \
   virtual void magicSizeGuard(Value::Iterator v) const { \
      static_assert(sizeof(*this) <= Value::Iterator::storage_size, "Type too large to fit in Value::Iterator"); \
      static_assert(alignof(decltype(*this)) <= Value::Iterator::storage_align, "Type too large to align in Value::Iterator"); \
   }

namespace BSON {

class Value::Iterator {
public:
   class Impl;
   class End;

   static const size_t storage_size = 60;
   static const size_t storage_align = 8;
   bool inited = false;

private:
   std::aligned_storage<storage_size, storage_align>::type storage;
   Impl *impl;
   Impl *clone_storage();

public:
   Iterator ();
   ~Iterator ();

   Iterator( const Iterator& other );
   const Iterator& operator=( const Iterator& other);
   Iterator ( const Iterator::Impl & i);

   Iterator &operator++();

   bool operator==(const Iterator &other) const;
   bool operator!=(const Iterator &other) const;

   const char *key() const;
   Value value() const;

   std::pair<const char *, Value> operator*();

   void print (std::ostream & stream) const;
};

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Iterator &obj);

#endif
