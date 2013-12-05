#include "bson_bsonc.hpp"
#include "bson_bsonc_utf8.hpp"
#include "bson_bsonc_doc.hpp"
#include "bson_bsonc_array.hpp"
#include "bson_value_impl_null.hpp"

namespace BSON {
BSONC::BSONC(Value::Type t) :
   Document (t),
   bson (bson_new(), &bson_destroy)
{
   append_ctx = bson.get();
}

std::string
BSONC::nextKey ()
{
   return std::to_string (lastKey++);
}

void
BSONC::toBson (void  **buf,
               size_t *len) const
{
   *buf = (void *)bson_get_data (bson.get ());
   *len = bson->len;
}

void
BSONC::append_single (const std::string & key,
                      int32_t             i)
{
   bson_append_int32 (append_ctx, key.c_str (), key.length (), i);
}

void
BSONC::append_single (const std::string & key,
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
      bson_append_document (append_ctx, key.c_str (), key.length (), &tmp);
      break;
      case Value::Type::Array:
      bson_append_array (append_ctx, key.c_str (), key.length (), &tmp);
      break;
   default:
      break;
   }
}

void
BSONC::append_single (const std::string & key,
               args_t args)
{
   args(key, *this);
}

void
BSONC::append_single (const std::string & key,
                      const std::string & s)
{
   bson_append_utf8 (append_ctx, key.c_str (), key.length (), s.c_str (),
                     s.length ());
}

void
BSONC::print (std::ostream & out) const
{
   char *str = bson_as_json (bson.get (), NULL);

   out << str;

   free (str);
}

Value
BSONC::operator [] (const std::string & s)
{
   Value r;
   bson_iter_t iter;
   bson_bool_t b;

   b = bson_iter_init_find (&iter, bson.get (), s.c_str ());

   if (!b) {
      r = Value (new Value::Impl::Null ());
   } else {
      switch (bson_iter_type (&iter)) {
      case BSON_TYPE_ARRAY:
         r = Value (new BSONC::Type::Array (bson, &iter));
         break;
      case BSON_TYPE_DOCUMENT:
         r = Value (new BSONC::Type::Doc (bson, &iter));
         break;
      case BSON_TYPE_UTF8:
         r = Value (new BSONC::Type::UTF8 (bson, bson_iter_utf8 (&iter, NULL)));
         break;
      default:
         r = Value (new Value::Impl::Null ());
         break;
      }
   }

   return r;
}
}
