#include "bson_value_impl_null.hpp"

namespace BSON {

Value::Impl::Null::Null () :
   Value::Impl(Value::Type::Null)
{
   static_assert(sizeof(Null) <= Value::storage_size, "Value::Impl::Null too large to fit in Value");
}

void Value::Impl::Null::print (std::ostream & stream) const
{
   stream << "NULL";
}

void Value::Impl::Null::clone(Value::Impl * storage) const
{
   new (storage) Value::Impl::Null();
}

}
