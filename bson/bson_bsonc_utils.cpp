#include "bson_bsonc_utils.hpp"
#include "bson_bsonc_utf8.hpp"
#include "bson_bsonc_doc.hpp"
#include "bson_bsonc_array.hpp"
#include "bson_value_impl_null.hpp"
#include "bson_value_impl_int32.hpp"

namespace BSON {

void BSONCUtils::pp (std::ostream & stream, bson_iter_t *iter, int indent, bool is_array)
{
   if (is_array) {
      stream << "[" << std::endl;
   } else {
      stream << "{" << std::endl;
   }

   indent += 2;

   while (bson_iter_next(iter)) {
      const char * key = bson_iter_key(iter);

      stream.width(indent);
      stream << "";
      stream.width(0);

      if (!is_array) {
         stream << key << " : ";
      }

      switch (bson_iter_type (iter)) {
      case BSON_TYPE_ARRAY:
      {
         bson_iter_t child;

         bson_iter_recurse(iter, &child);

         pp(stream, &child, indent, true);

         break;
      }
      case BSON_TYPE_DOCUMENT:
      {
         bson_iter_t child;

         bson_iter_recurse(iter, &child);

         pp(stream, &child, indent, false);
         break;
      }
      case BSON_TYPE_UTF8:
         stream << bson_iter_utf8 (iter, NULL);
         break;
      case BSON_TYPE_INT32:
         stream << bson_iter_int32 (iter);
         break;
      default:
         stream << "NULL";
         break;
      }

      stream << "," << std::endl;
   }

   indent -= 2;

   stream.width(indent);
   stream << "";
   stream.width(0);

   if (is_array) {
      stream << "]";
   } else {
      stream << "}";
   }
}

Value BSONCUtils::convert (const std::shared_ptr<bson_t> & root, const bson_t * bson, const char * key)
{
   Value r;
   bson_iter_t iter;
   bson_bool_t b;

   b = bson_iter_init_find (&iter, bson, key);

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
