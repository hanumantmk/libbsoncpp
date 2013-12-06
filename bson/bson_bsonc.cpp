#include "bson_bsonc.hpp"
#include "bson_bsonc_utils.hpp"

namespace BSON {
BSONC::BSONC(Value::Type t) :
   Document (t),
   bson (bson_new(), &bson_destroy),
   append_ctx (bson.get())
{
}

BSONC::BSONC(Value::Type t, const std::shared_ptr<bson_t> &b) :
   Document (t),
   bson (b),
   append_ctx (bson.get())
{
}

void BSONC::BSONC::clone(Value::Impl * storage) const
{
   new (storage) BSONC::BSONC(type, bson);
}

const char *
BSONC::nextKey ()
{
   sprintf(lastKeyBuf, "%d", lastKey++);
   return (lastKeyBuf);
}

void
BSONC::toBson (void  **buf,
               size_t *len) const
{
   *buf = (void *)bson_get_data (bson.get ());
   *len = bson->len;
}

void
BSONC::append_single (const char * key,
                      int32_t             i)
{
   bson_append_int32 (append_ctx, key, -1, i);
}

void
BSONC::append_single (const char * key,
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
      bson_append_document (append_ctx, key, -1, &tmp);
      break;
      case Value::Type::Array:
      bson_append_array (append_ctx, key, -1, &tmp);
      break;
   default:
      break;
   }
}

void
BSONC::append_single (const char * key,
               args_t args)
{
   args(key, *this);
}

void
BSONC::append_single (const char * key,
                      const char * s)
{
   bson_append_utf8 (append_ctx, key, -1, s, -1);
}

void
BSONC::print (std::ostream & out) const
{
   bson_iter_t iter;

   bson_iter_init(&iter, bson.get());

   BSONCUtils::pp( out, &iter, 0, false);
}

Value
BSONC::operator [] (const char * s) const
{
   return BSONCUtils::convert(bson, bson.get(), s);
}

}
