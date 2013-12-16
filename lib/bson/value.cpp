#include "bson/value.hpp"
#include "bson/value_impl.hpp"
#include "bson/iterator.hpp"
#include "bson/types.hpp"

namespace BSON {

Value::Value()
{
}

auto Value::clone_storage() -> Impl *
{
   return static_cast<Impl *>(static_cast<void*>(&storage));
}

Value::Value(const Value& other) :
   Value()
{
   impl = other.impl->clone(clone_storage());
}

Value::Value ( const Value::Impl & i) :
   Value()
{
   impl = i.clone(clone_storage());
}

Value::Value(const char * str) :
   Value()
{
   impl = new (clone_storage()) BSON::Type (Types::Utf8(str));
}


Value::Value(int32_t i) :
   Value()
{
   impl = new (clone_storage()) BSON::Type (Types::Int32(i));
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

std::tuple<const uint8_t *, size_t> Value::to_bson() const
{
   return impl->to_bson();
}

Value Value::operator [] (const char * s) const
{
   return (*impl)[s];
}

Value Value::operator [] (int i) const
{
   return (*impl)[i];
}

auto Value::begin() const -> Iterator
{
   return impl->begin();
}

auto Value::end() const -> Iterator
{
   return impl->end();
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
