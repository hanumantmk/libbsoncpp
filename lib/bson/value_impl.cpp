#include "bson/value_impl.hpp"
#include "bson/iterator.hpp"

namespace BSON {

const char * ValueImpl::to_utf8() const
{
   throw ValueException("No conversion to UTF8");
}

int32_t ValueImpl::to_int32() const
{
   throw ValueException("No conversion to int32");
}

std::tuple<const uint8_t *, size_t> ValueImpl::to_bson() const
{
   throw ValueException("No conversion to bson");
}

Value ValueImpl::operator[](const char * str) const
{
   throw ValueException("No conversion to document available");
}

Value ValueImpl::operator[](int i) const
{
   throw ValueException("No conversion to array available");
}

Document & ValueImpl::to_document()
{
   throw ValueException("No conversion to document available");
}

ValueIterator ValueImpl::begin() const
{
   throw ValueException("No begin() available");
}

ValueIterator ValueImpl::end() const
{
   throw ValueException("No end() available");
}

}

std::ostream & operator << (std::ostream & out, const BSON::ValueImpl &obj)
{
   obj.print(out);

   return out;
}
