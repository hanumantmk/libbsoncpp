#include "bson_bsonc_doc.hpp"
#include "bson_bsonc_utils.hpp"

namespace BSON {

BSONC::Type::Doc::Doc (const std::shared_ptr<BSONC::Impl> &i, const bson_uint8_t *b, bson_uint32_t l) :
   BSONC::Type (Value::Type::Document, i),
   len(l),
   buf(b)
{
}

void
BSONC::Type::Doc::print (std::ostream & stream) const
{
   bson_t child;
   bson_iter_t iter;

   bson_init_static(&child, buf, len);
   bson_iter_init(&iter, &child);

   BSONCUtils::pp( stream, &iter, 0, false);
}

void BSONC::Type::Doc::clone(Value::Impl * storage) const
{
   new (storage) BSONC::Type::Doc(impl, buf, len);
}

Value
BSONC::Type::Doc::operator [] (const char * s) const
{
   bson_t child;
   bson_init_static(&child, buf, len);

   return BSONCUtils::convert(impl, &child, s);
}

}
