#include "bson/bsonc_utils.hpp"
#include "bson/bsonc_type.hpp"
#include "bson/types.hpp"

namespace BSON {

void BSONCUtils::pp_type (std::ostream & stream, bson_iter_t *iter, int indent)
{
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
         stream << bson_iter_utf8 (iter, nullptr);
         break;
      case BSON_TYPE_INT32:
         stream << bson_iter_int32 (iter);
         break;
      default:
         stream << "NULL";
         break;
      }

}

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

      pp_type(stream, iter, indent);

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

Value BSONCUtils::convert (const bson_t * root, const bson_iter_t * iter)
{
   return Value(BSONCType(root, iter));
}

Value BSONCUtils::convert (const bson_t *root, const bson_t * bson, const char * key)
{
   using namespace Types;

   bson_iter_t iter;
   bson_bool_t b;

   b = bson_iter_init_find (&iter, bson, key);

   if (!b) {
      return Value(Type(Null()));
   } else {
      return convert (root, &iter);
   }
}

}
