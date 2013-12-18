#ifndef BSONCPP_VALUE_ITERATOR_H
#define BSONCPP_VALUE_ITERATOR_H

#include "bson/value.hpp"

#define BSONCPP_VALUE_ITERATOR_GUARD \
protected: \
   virtual void magicSizeGuard(ValueIterator v) const { \
      static_assert(sizeof(*this) <= ValueIterator::storage_size, "Type too large to fit in ValueIterator"); \
      static_assert(alignof(decltype(*this)) <= ValueIterator::storage_align, "Type too large to align in ValueIterator"); \
   }

namespace BSON {

class ValueIteratorImpl;

class ValueIterator {
public:
   static const size_t storage_size = 60;
   static const size_t storage_align = 8;

private:
   std::aligned_storage<storage_size, storage_align>::type storage;
   ValueIteratorImpl *impl;
   ValueIteratorImpl *clone_storage();

public:
   ValueIterator ();
   ~ValueIterator ();

   ValueIterator( const ValueIterator& other );
   const ValueIterator& operator=( const ValueIterator& other);
   ValueIterator ( const ValueIteratorImpl & i);

   ValueIterator &operator++();

   bool operator==(const ValueIterator &other) const;
   bool operator!=(const ValueIterator &other) const;

   const char *key() const;
   Value value() const;

   std::pair<const char *, Value> operator*();

   void print (std::ostream & stream) const;
};

}

std::ostream & operator << (std::ostream & out, const BSON::ValueIterator &obj);

#endif
