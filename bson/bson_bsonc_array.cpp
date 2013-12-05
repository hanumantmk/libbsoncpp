#include "bson_bsonc_array.hpp"

namespace BSON {
BSONC::Type::Array::Array (const std::shared_ptr<bson_t> &i,
                           bson_iter_t                   *t) :
   BSONC::Type (Value::Type::Array, i)
{
   const bson_uint8_t *buf;
   bson_uint32_t len;

   bson_iter_array (t, &len, &buf);

   bson_init_static (&child, buf, len);
}

void
BSONC::Type::Array::print (std::ostream & stream) const
{
   char *str = bson_as_json (&child, NULL);

   stream << str;

   free (str);
}
}
