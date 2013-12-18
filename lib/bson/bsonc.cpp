#include "bson/bsonc.hpp"
#include "bson/bsonc_impl.hpp"
#include "bson/bsonc_type.hpp"
#include "bson/bsonc_utils.hpp"

#include <sstream>

namespace BSON {
BSONC::BSONC() :
   impl (new BSONC::Impl())
{

}

BSONC::BSONC(const std::shared_ptr<BSONC::Impl> &i) :
   impl (i)
{
}


Document & BSONC::to_document ()
{
   return *this;
}

Value::Type BSONC::get_type () const
{
   return Value::Type::Document;
}

auto BSONC::clone(Value::Impl * storage) const -> Value::Impl *
{
   return new (storage) BSONC(impl);
}

void BSONC::throwArgs(const char * key, const char * msg)
{
   append_single(key, "XXX <--- Error here");

   while (impl->top() != impl->bottom()) {
      impl->pop();
   }
   std::stringstream ss;

   ss << msg << std::endl << "Current struct: " << *this;

   throw Exception(ss.str().c_str());
}

void BSONC::push(const char *key, bool is_array)
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
BSONC::append_single ( const char * key,
                      const Value&    v)
{
   switch (v.get_type()) {
      case Value::Type::Utf8:
         bson_append_utf8(impl->top(), key, -1, v.to_utf8(), -1);
         break;
      case Value::Type::Int32:
         bson_append_int32(impl->top(), key, -1, v.to_int32());
         break;
      case Value::Type::Document:
      case Value::Type::Array:
      {
         const uint8_t *buf;
         size_t len;
         bson_t tmp;

         std::tie(buf, len) = v.to_bson();

         bson_init_static (&tmp, (const bson_uint8_t *)buf, len);

         if (v.get_type() == Value::Type::Document) {
            bson_append_document (impl->top(), key, -1, &tmp);
         } else {
            bson_append_array (impl->top(), key, -1, &tmp);
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

Value::Iterator BSONC::begin() const
{
   bson_iter_t iter;
   bson_iter_init(&iter, impl->bottom());
   bson_iter_next(&iter);

   return Value::Iterator(BSONC::Type(impl->bottom(), &iter));
}

Value::Iterator BSONC::end() const
{
   return Value::Iterator::End();
}

}
