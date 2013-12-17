#include "bson/value_impl.hpp"
#include "bson/iterator.hpp"

namespace BSON {

const char * Value::Impl::to_utf8() const
{
   throw Value::Exception("No conversion to UTF8");
}

int32_t Value::Impl::to_int32() const
{
   throw Value::Exception("No conversion to int32");
}

std::tuple<const uint8_t *, size_t> Value::Impl::to_bson() const
{
   throw Value::Exception("No conversion to bson");
}

Value Value::Impl::operator[](const char * str) const
{
   throw Value::Exception("No conversion to document available");
}

Value Value::Impl::operator[](int i) const
{
   throw Value::Exception("No conversion to array available");
}

Document & Value::Impl::to_document()
{
   throw Value::Exception("No conversion to document available");
}

Value::Iterator Value::Impl::begin() const
{
   throw Value::Exception("No begin() available");
}

Value::Iterator Value::Impl::end() const
{
   throw Value::Exception("No end() available");
}

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Impl &obj)
{
   obj.print(out);

   return out;
}
