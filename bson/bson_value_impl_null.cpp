#include "bson_value_impl_null.hpp"

namespace BSON {

Value::Impl::Null::Null () :
   Value::Impl(Value::Type::Null)
{
}

void Value::Impl::Null::print (std::ostream & stream) const
{
   stream << "NULL";
}

}
