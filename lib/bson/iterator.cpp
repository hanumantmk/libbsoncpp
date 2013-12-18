#include "bson/iterator.hpp"
#include "bson/iterator_impl.hpp"

namespace BSON {

ValueIterator::ValueIterator()
{
}

auto ValueIterator::clone_storage() -> ValueIteratorImpl *
{
   return static_cast<ValueIteratorImpl *>(static_cast<void*>(&storage));
}

ValueIterator::ValueIterator(const ValueIterator& other) :
   ValueIterator()
{
   impl = other.impl->clone(clone_storage());
}

ValueIterator::ValueIterator ( const ValueIteratorImpl & i) :
   ValueIterator()
{
   impl = i.clone(clone_storage());
}

auto ValueIterator::operator=( const ValueIterator& other) -> const ValueIterator &
{
   impl = other.impl->clone(clone_storage());

   return *this;
}

ValueIterator::~ValueIterator()
{
   impl->~ValueIteratorImpl();
}

auto ValueIterator::operator++() -> ValueIterator &
{
   impl->next();

   return *this;
}

bool ValueIterator::operator==(const ValueIterator &other) const
{
   return impl->is_equal(*(other.impl));
}

bool ValueIterator::operator!=(const ValueIterator &other) const
{
   return ! impl->is_equal(*(other.impl));
}

const char * ValueIterator::key() const
{
   return impl->key();
}

Value ValueIterator::value() const
{
   return impl->to_value();
}

std::pair<const char *, Value>
ValueIterator::operator*()
{
   return std::make_pair(impl->key(), impl->to_value());
}

void
ValueIterator::print (std::ostream & stream) const
{
   impl->print(stream);
}

}

std::ostream & operator << (std::ostream & out, const BSON::ValueIterator &obj)
{
   obj.print(out);

   return out;
}
