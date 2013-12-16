#ifndef BSONCPP_VALUE_ITERATOR_IMPL_H
#define BSONCPP_VALUE_ITERATOR_IMPL_H

#include "bson/iterator.hpp"

namespace BSON {

class Value::Iterator::Impl {
protected:
   virtual void magicSizeGuard(Value::Iterator v) const = 0;

public:
   virtual ~Impl() {}

   virtual Impl * clone(Impl * storage) const = 0;

   virtual void next() = 0;

   virtual bool is_equal(const Impl &other) const = 0;
   virtual bool is_end() const = 0;

   virtual Value to_value() const = 0;
   virtual const char * key() const = 0;

   virtual void print (std::ostream & stream) const {};
};

class Value::Iterator::End : public Value::Iterator::Impl {
public:
   End();

   Impl * clone(Impl * storage) const;

   void next();

   bool is_equal(const Impl &other) const;
   bool is_end() const;

   Value to_value() const;
   const char * key() const;

   BSONCPP_VALUE_ITERATOR_GUARD;
};

}

#endif
