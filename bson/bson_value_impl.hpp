#ifndef BSONCPP_VALUE_IMPL_H
#define BSONCPP_VALUE_IMPL_H

#include "bson_value.hpp"

namespace BSON {

class Value::Impl {
public:
   class Null;

protected:
   Type type;
   Impl (Type t);
   virtual void magicSizeGuard() const = 0;

public:
   Type
   get_type () const;

   virtual ~Impl()
   {
   };

   virtual void clone(Impl * storage) const = 0;

   virtual void
   print (std::ostream & stream) const
   {
   }
};

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Impl &obj);

#endif
