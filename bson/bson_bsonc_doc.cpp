#include "bson_bsonc_doc.hpp"
#include "bson_bsonc_utils.hpp"

namespace BSON {

BSONC::Type::Doc::Doc (const std::shared_ptr<bson_t> &i, const bson_uint8_t *b, bson_uint32_t l) :
   BSONC::Type (Value::Type::Document, i),
   len(l),
   buf(b)
{
}

void
BSONC::Type::Doc::print (std::ostream & stream) const
{
   bson_t child;

   bson_init_static(&child, buf, len);

   char *str = bson_as_json (&child, NULL);

   stream << str;

   free (str);
}

void BSONC::Type::Doc::clone(Value::Impl * storage) const
{
   new (storage) BSONC::Type::Doc(bson, buf, len);
}

Value
BSONC::Type::Doc::operator [] (const std::string & s) const
{
   bson_t child;
   bson_init_static(&child, buf, len);

   return BSONCUtils::convert(bson, &child, s);
}

}
