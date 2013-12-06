#include "bson_value_impl_int32.hpp"

namespace BSON {

Value::Impl::Int32::Int32 (int32_t i) :
   Value::Impl(Value::Type::Int32),
   val(i)
{
}

void Value::Impl::Int32::print (std::ostream & stream) const
{
   stream << val;
}

void Value::Impl::Int32::clone(Value::Impl * storage) const
{
   new (storage) Value::Impl::Int32(val);
}

}
