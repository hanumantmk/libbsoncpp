#include "bson/iterator_impl.hpp"

namespace BSON {

ValueIteratorEnd::ValueIteratorEnd() { }

void ValueIteratorEnd::next()
{
   throw ValueException("No support for next()");
}

bool ValueIteratorEnd::is_equal(const ValueIteratorImpl &other) const
{
   return is_end() && other.is_end();
}

bool ValueIteratorEnd::is_end() const
{
   return true;
}

Value
ValueIteratorEnd::to_value() const
{
   throw ValueException("No support for to_value()");
}

const char *
ValueIteratorEnd::key() const
{
   throw ValueException("No support for key()");
}

auto ValueIteratorEnd::clone(ValueIteratorImpl * storage) const -> ValueIteratorImpl *
{
   return new (storage) ValueIteratorEnd();
}

}
