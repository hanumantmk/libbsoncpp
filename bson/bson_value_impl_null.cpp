#include "bson_value_impl_null.hpp"

namespace BSON {

Value::Impl::Null::Null ()
{
}

Value::Type
Value::Impl::Null::get_type() const
{
   return Value::Type::Null;
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
