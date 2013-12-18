#include "bson/bsonc.hpp"
#include "bson/bsonc_impl.hpp"
#include "bson/bsonc_type.hpp"
#include "bson/bsonc_utils.hpp"

#include <sstream>

namespace BSON {
BSONC::BSONC() :
   impl (new BSONCImpl())
{

}

BSONC::BSONC(const std::shared_ptr<BSONCImpl> &i) :
   impl (i)
{
}


Document & BSONC::to_document ()
{
   return *this;
}

ValueType BSONC::get_type () const
{
   return ValueType::Document;
}

auto BSONC::clone(ValueImpl * storage) const -> ValueImpl *
{
   return new (storage) BSONC(impl);
}

void BSONC::throwArgs(const std::string & key, const char * msg)
{
   append_single(key, "XXX <--- Error here");

   while (impl->top() != impl->bottom()) {
      impl->pop();
   }
   std::stringstream ss;

   ss << msg << std::endl << "Current struct: " << *this;

   throw Exception(ss.str().c_str());
}

void BSONC::push(const std::string & key, bool is_array)
{
   impl->push(key, is_array);
}

bool BSONC::in_progress()
{
   return impl->top() != impl->bottom();
}

void BSONC::pop()
{
   impl->pop();
}

const char * BSONC::nextKey()
{
   return impl->nextKey();
}

bool BSONC::is_array()
{
   return impl->is_array();
}

std::tuple<const uint8_t *, size_t> BSONC::to_bson() const
{
   bson_t *bson = impl->bottom();
   return make_tuple(bson_get_data (bson), bson->len);
}

void
BSONC::append_single ( const std::string & key,
                      const Value&    v)
{
   switch (v.get_type()) {
      case ValueType::Utf8:
         bson_append_utf8(impl->top(), key.c_str(), key.length(), v.to_utf8(), -1);
         break;
      case ValueType::Int32:
         bson_append_int32(impl->top(), key.c_str(), key.length(), v.to_int32());
         break;
      case ValueType::Document:
      case ValueType::Array:
      {
         const uint8_t *buf;
         size_t len;
         bson_t tmp;

         std::tie(buf, len) = v.to_bson();

         bson_init_static (&tmp, (const bson_uint8_t *)buf, len);

         if (v.get_type() == ValueType::Document) {
            bson_append_document (impl->top(), key.c_str(), key.length(), &tmp);
         } else {
            bson_append_array (impl->top(), key.c_str(), key.length(), &tmp);
         }
      }
      default:
         break;
   }
}

void
BSONC::print (std::ostream & out) const
{
   bson_iter_t iter;

   bson_iter_init(&iter, impl->bottom());

   BSONCUtils::pp( out, &iter, 0, false);
}

Value
BSONC::operator [] (const char * s) const
{
   return BSONCUtils::convert(impl->bottom(), impl->bottom(), s);
}

ValueIterator BSONC::begin() const
{
   bson_iter_t iter;
   bson_iter_init(&iter, impl->bottom());
   bson_iter_next(&iter);

   return ValueIterator(BSONCType(impl->bottom(), &iter));
}

ValueIterator BSONC::end() const
{
   return ValueIteratorEnd();
}

void BSONC::clear()
{
   impl->clear();
}

}
