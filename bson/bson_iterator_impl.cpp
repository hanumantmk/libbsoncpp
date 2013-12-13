#include "bson_iterator_impl.hpp"

namespace BSON {

Value::Iterator::End::End() { }

void Value::Iterator::End::next()
{
   throw Value::Exception("No support for next()");
}

bool Value::Iterator::End::is_equal(const Impl &other) const
{
   return is_end() && other.is_end();
}

bool Value::Iterator::End::is_end() const
{
   return true;
}

Value
Value::Iterator::End::to_value() const
{
   throw Value::Exception("No support for to_value()");
}

const char *
Value::Iterator::End::key() const
{
   throw Value::Exception("No support for key()");
}

auto Value::Iterator::End::clone(Impl * storage) const -> Impl *
{
   return new (storage) End();
}

}
