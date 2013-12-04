#include "bson_value.hpp"
#include "bson_value_impl.hpp"

namespace BSON {

Value::Value() {}

Value::Type
Value::get_type () const
{
   return impl->get_type ();
}

void
Value::print (std::ostream & stream) const
{
   impl->print(stream);
}

}

std::ostream & operator << (std::ostream & out, const BSON::Value &obj)
{
   obj.print(out);

   return out;
}

