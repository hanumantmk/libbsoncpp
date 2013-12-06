#include "bson_value.hpp"
#include "bson_value_impl.hpp"

namespace BSON {

Value::Value() :
   impl(static_cast<Impl *>(static_cast<void*>(&storage)))
{
}

Value::Value(const Value& other) :
   Value()
{
   other.impl->clone(impl);
}


const Value& Value::operator=( const Value& other)
{
   other.impl->clone(impl);

   return *this;
}

Value::~Value()
{
   impl->~Impl();
}

Value::Impl *
Value::get_impl ()
{
   return impl;
}

Value::Type
Value::get_type () const
{
   return impl->get_type ();
}

const char * Value::to_utf8() const
{
   return impl->to_utf8();
}

int32_t Value::to_int32() const
{
   return impl->to_int32();
}

Value Value::operator [] (const std::string & s) const
{
   return (*impl)[s];
}

Value Value::operator [] (int i) const
{
   return (*impl)[i];
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
