#include "bson_value_impl.hpp"

namespace BSON {

Value::Impl::Impl(Value::Type t) :
   type(t)
{
}

Value::Type
Value::Impl::get_type() const
{
   return type;
}

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Impl &obj)
{
   obj.print(out);

   return out;
}
