#ifndef BSONCPP_VALUE_IMPL_NULL_H
#define BSONCPP_VALUE_IMPL_NULL_H

#include "bson_value_impl.hpp"

namespace BSON {

class Value::Impl::Null : public Value::Impl {
public:
   Null ();

   virtual void
   print (std::ostream & stream) const;
};

}

#endif
