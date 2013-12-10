#include "bson_bsonc_doc.hpp"
#include "bson_bsonc_utils.hpp"

namespace BSON {

BSONC::Types::Doc::Doc (const std::shared_ptr<BSONC::Impl> &i, const bson_uint8_t *b, bson_uint32_t l) :
   BSONC::Type<Value::Type::Document> (i),
   len(l),
   buf(b)
{
}

void
BSONC::Types::Doc::print (std::ostream & stream) const
{
   bson_t child;
   bson_iter_t iter;

   bson_init_static(&child, buf, len);
   bson_iter_init(&iter, &child);

   BSONCUtils::pp( stream, &iter, 0, false);
}

void BSONC::Types::Doc::clone(Value::Impl * storage) const
{
   new (storage) BSONC::Types::Doc(impl, buf, len);
}

Value
BSONC::Types::Doc::operator [] (const char * s) const
{
   bson_t child;
   bson_init_static(&child, buf, len);

   return BSONCUtils::convert(impl, &child, s);
}

}
