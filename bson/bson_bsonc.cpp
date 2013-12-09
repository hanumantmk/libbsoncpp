#include "bson_bsonc.hpp"
#include "bson_bsonc_impl.hpp"
#include "bson_bsonc_utils.hpp"

namespace BSON {
BSONC::BSONC() :
   Document (Value::Type::Root),
   impl (new BSONC::Impl())
{

}

BSONC::BSONC(Value::Type t) :
   Document (t),
   impl (new BSONC::Impl())
{
}

BSONC::BSONC(Value::Type t, const std::shared_ptr<BSONC::Impl> &i) :
   Document (t),
   impl (i)
{
}

void BSONC::clone(Value::Impl * storage) const
{
   new (storage) BSONC(type, impl);
}

void BSONC::push(const char *key, bool is_array)
{
   impl->push(key, is_array);
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

void
BSONC::toBson (void  **buf,
               size_t *len) const
{
   bson_t *bson = impl->top();
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
      case Value::Type::Root:
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
               const Token::Doc & t)
{
   impl->push(key, false);
}

void
BSONC::append_single ( const char * key,
               const Token::Array & t)
{
   impl->push(key, true);
}

void
BSONC::append_single ( const char * key,
               args_t args)
{
   args(key, *this);
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

   bson_iter_init(&iter, impl->top());

   BSONCUtils::pp( out, &iter, 0, false);
}

Value
BSONC::operator [] (const char * s) const
{
   return BSONCUtils::convert(impl, impl->top(), s);
}

}
