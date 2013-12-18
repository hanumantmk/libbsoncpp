#include "bson/value.hpp"
#include "bson/value_impl.hpp"
#include "bson/iterator.hpp"
#include "bson/types.hpp"

namespace BSON {

Value::Value()
{
}

auto Value::clone_storage() -> ValueImpl *
{
   return static_cast<ValueImpl *>(static_cast<void*>(&storage));
}

Value::Value(const Value& other) :
   Value()
{
   if (other.has_value()) {
      impl = other.impl->clone(clone_storage());
   }
}

Value::Value ( const ValueImpl & i) :
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
   if (other.has_value()) {
      impl = other.impl->clone(clone_storage());
   } else {
      if (impl) {
         impl->~ValueImpl();
         impl = NULL;
      }
   }

   return *this;
}

Value::~Value()
{
   if (impl) {
      impl->~ValueImpl();
   }
}

ValueType
Value::get_type () const
{
   return impl->get_type ();
}

bool
Value::has_value () const
{
   return impl != NULL;
}

Value::operator bool() const
{
   return has_value();
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

Document & Value::to_document()
{
   return impl->to_document();
}

auto Value::begin() const -> ValueIterator
{
   return impl->begin();
}

auto Value::end() const -> ValueIterator
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
