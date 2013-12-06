#include "bson_bsonc_utils.hpp"
#include "bson_bsonc_utf8.hpp"
#include "bson_bsonc_doc.hpp"
#include "bson_bsonc_array.hpp"
#include "bson_value_impl_null.hpp"
#include "bson_value_impl_int32.hpp"

namespace BSON {

Value BSONCUtils::convert (const std::shared_ptr<bson_t> & root, const bson_t * bson, const std::string & s)
{
   Value r;
   bson_iter_t iter;
   bson_bool_t b;

   b = bson_iter_init_find (&iter, bson, s.c_str());

   if (!b) {
      new (r.get_impl()) Value::Impl::Null ();
   } else {
      switch (bson_iter_type (&iter)) {
      case BSON_TYPE_ARRAY:
      {
         const bson_uint8_t *buf;
         bson_uint32_t len;

         bson_iter_array(&iter, &len, &buf);
         new (r.get_impl()) BSONC::Type::Array (root, buf, len);
         break;
      }
      case BSON_TYPE_DOCUMENT:
      {
         const bson_uint8_t *buf;
         bson_uint32_t len;

         bson_iter_document(&iter, &len, &buf);
         new (r.get_impl()) BSONC::Type::Doc (root, buf, len);
         break;
      }
      case BSON_TYPE_UTF8:
         new (r.get_impl()) BSONC::Type::UTF8 (root, bson_iter_utf8 (&iter, NULL));
         break;
      case BSON_TYPE_INT32:
         new (r.get_impl()) Value::Impl::Int32 (bson_iter_int32 (&iter));
         break;
      default:
         new (r.get_impl()) Value::Impl::Null ();
         break;
      }
   }

   return r;
}

}
