#include "bson_bsonc_array.hpp"
#include "bson_bsonc_utils.hpp"

namespace BSON {

BSONC::Type::Array::Array (const std::shared_ptr<bson_t> &i, const bson_uint8_t *b, bson_uint32_t l) :
   BSONC::Type (Value::Type::Array, i),
   len(l),
   buf(b)
{
}

void
BSONC::Type::Array::print (std::ostream & stream) const
{
   bson_t child;

   bson_init_static(&child, buf, len);

   char *str = bson_as_json (&child, NULL);

   stream << str;

   free (str);
}

void BSONC::Type::Array::clone(Value::Impl * storage) const
{
   new (storage) BSONC::Type::Array(bson, buf, len);
}

Value
BSONC::Type::Array::operator [] (int i) const
{
   bson_t child;
   bson_init_static(&child, buf, len);

   return BSONCUtils::convert(bson, &child, std::to_string (i));
}

}
