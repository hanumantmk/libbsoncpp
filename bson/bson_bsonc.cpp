#include "bson_bsonc.hpp"
#include "bson_bsonc_impl.hpp"
#include "bson_bsonc_utils.hpp"

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


Value::Type BSONC::get_type () const
{
   return Value::Type::Document;
}

void BSONC::clone(Value::Impl * storage) const
{
   new (storage) BSONC(impl);
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

void BSONC::pop(bool arr)
{
   if (impl->top() == impl->bottom()) {
      throwArgs("", "Attempting to close the root document");
   }

   if (arr != is_array()) {
      throwArgs("", "mismatched sub document close");
   }
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

void
BSONC::toBson (void  **buf,
               size_t *len) const
{
   bson_t *bson = impl->bottom();
   *buf = (void *)bson_get_data (bson);
   *len = bson->len;
}

void
BSONC::append_single ( const char * key,
                      int32_t             i)
{
   bson_append_int32 (impl->top(), key, -1, i);
}

void
BSONC::append_single ( const char * key,
                      const Document &    b)
{
   void *buf;
   size_t len;
   bson_t tmp;

   b.toBson (&buf, &len);

   bson_init_static (&tmp, (const bson_uint8_t *)buf, len);

   switch (b.get_type ()) {
      case Value::Type::Document:
      bson_append_document (impl->top(), key, -1, &tmp);
      break;
      case Value::Type::Array:
      bson_append_array (impl->top(), key, -1, &tmp);
      break;
   default:
      break;
   }
}

void
BSONC::append_single ( const char * key,
                      const char * s)
{
   bson_append_utf8 (impl->top(), key, -1, s, -1);
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
   return BSONCUtils::convert(impl, impl->bottom(), s);
}

}
