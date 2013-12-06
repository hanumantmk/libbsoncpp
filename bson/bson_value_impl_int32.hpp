#ifndef BSONCPP_VALUE_IMPL_INT32_H
#define BSONCPP_VALUE_IMPL_INT32_H

#include "bson_value_impl.hpp"

namespace BSON {

class Value::Impl::Int32 : public Value::Impl {
private:
   int32_t val;

public:
   Int32 (int32_t i);

   void
   print (std::ostream & stream) const;

   void clone(Impl * storage) const;

   BSONCPP_VALUE_GUARD(Value::Impl::Int32)
};

}

#endif
