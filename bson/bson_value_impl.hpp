#ifndef BSONCPP_VALUE_IMPL_H
#define BSONCPP_VALUE_IMPL_H

#include "bson_value.hpp"

namespace BSON {

class Value::Impl {
public:
   class Null;
   class Int32;

protected:
   virtual void magicSizeGuard() const = 0;

public:
   virtual Type get_type () const = 0;

   virtual ~Impl()
   {
   };

   virtual void clone(Impl * storage) const = 0;

   virtual const char * to_utf8() const;
   virtual int32_t to_int32() const;

   virtual Value operator [] (const char * s) const;
   virtual Value operator [] (int i) const;

   virtual void
   print (std::ostream & stream) const
   {
   }
};

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Impl &obj);

#endif
