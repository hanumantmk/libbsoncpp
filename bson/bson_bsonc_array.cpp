#include "bson_bsonc_array.hpp"
#include "bson_bsonc_utils.hpp"

namespace BSON {

BSONC::Types::Array::Array (const std::shared_ptr<BSONC::Impl> &i, const bson_uint8_t *b, bson_uint32_t l) :
   BSONC::Type<Value::Type::Array> (i),
   len(l),
   buf(b)
{
}

void
BSONC::Types::Array::print (std::ostream & stream) const
{
   bson_t child;
   bson_iter_t iter;

   bson_init_static(&child, buf, len);
   bson_iter_init(&iter, &child);

   BSONCUtils::pp( stream, &iter, 0, true);
}

void BSONC::Types::Array::clone(Value::Impl * storage) const
{
   new (storage) BSONC::Types::Array(impl, buf, len);
}

Value
BSONC::Types::Array::operator [] (int i) const
{
   bson_t child;
   bson_init_static(&child, buf, len);

   char str[30];
   sprintf(str, "%d", i);

   return BSONCUtils::convert(impl, &child, str);
}

}
