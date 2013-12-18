#ifndef BSONCPP_VALUE_ITERATOR_IMPL_H
#define BSONCPP_VALUE_ITERATOR_IMPL_H

#include "bson/iterator.hpp"

namespace BSON {

class ValueIteratorImpl {
protected:
   virtual void magicSizeGuard(ValueIterator v) const = 0;

public:
   virtual ~ValueIteratorImpl() {}

   virtual ValueIteratorImpl * clone(ValueIteratorImpl * storage) const = 0;

   virtual void next() = 0;

   virtual bool is_equal(const ValueIteratorImpl &other) const = 0;
   virtual bool is_end() const = 0;

   virtual Value to_value() const = 0;
   virtual const char * key() const = 0;

   virtual void print (std::ostream & stream) const {};
};

class ValueIteratorEnd : public ValueIteratorImpl {
public:
   ValueIteratorEnd();

   ValueIteratorImpl * clone(ValueIteratorImpl * storage) const;

   void next();

   bool is_equal(const ValueIteratorImpl &other) const;
   bool is_end() const;

   Value to_value() const;
   const char * key() const;

   BSONCPP_VALUE_ITERATOR_GUARD;
};

}

#endif
