#include "bson_value_impl_int32.hpp"

namespace BSON {

Value::Impl::Int32::Int32 (int32_t i) :
   val(i)
{
}

Value::Type
Value::Impl::Int32::get_type() const
{
   return Value::Type::Int32;
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
