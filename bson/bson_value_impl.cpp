#include "bson_value_impl.hpp"

namespace BSON {

const char * Value::Impl::to_utf8() const
{
   throw Value::Exception("No conversion to UTF8");
}

int32_t Value::Impl::to_int32() const
{
   throw Value::Exception("No conversion to int32");
}

Value Value::Impl::operator[](const char * str) const
{
   throw Value::Exception("No conversion to document available");
}

Value Value::Impl::operator[](int i) const
{
   throw Value::Exception("No conversion to array available");
}

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Impl &obj)
{
   obj.print(out);

   return out;
}
