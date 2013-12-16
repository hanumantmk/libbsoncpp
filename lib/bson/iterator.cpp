#include "bson/iterator.hpp"
#include "bson/iterator_impl.hpp"

namespace BSON {

Value::Iterator::Iterator() :
   inited(true)
{
}

auto Value::Iterator::clone_storage() -> Impl *
{
   return static_cast<Impl *>(static_cast<void*>(&storage));
}

Value::Iterator::Iterator(const Iterator& other) :
   Iterator()
{
   impl = other.impl->clone(clone_storage());
}

Value::Iterator::Iterator ( const Iterator::Impl & i) :
   Iterator()
{
   impl = i.clone(clone_storage());
}

auto Value::Iterator::operator=( const Iterator& other) -> const Iterator &
{
   impl = other.impl->clone(clone_storage());

   return *this;
}

Value::Iterator::~Iterator()
{
   impl->~Impl();
}

auto Value::Iterator::operator++() -> Iterator &
{
   impl->next();

   return *this;
}

bool Value::Iterator::operator==(const Iterator &other) const
{
   return impl->is_equal(*(other.impl));
}

bool Value::Iterator::operator!=(const Iterator &other) const
{
   return ! impl->is_equal(*(other.impl));
}

const char * Value::Iterator::key() const
{
   return impl->key();
}

Value Value::Iterator::value() const
{
   return impl->to_value();
}

std::pair<const char *, Value>
Value::Iterator::operator*()
{
   return std::make_pair(impl->key(), impl->to_value());
}

void
Value::Iterator::print (std::ostream & stream) const
{
   impl->print(stream);
}

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Iterator &obj)
{
   obj.print(out);

   return out;
}
