#include "bson_bsonc_doc.hpp"

namespace BSON {
BSONC::Type::Doc::Doc (const std::shared_ptr<bson_t> &i,
                       bson_iter_t                   *t) :
   BSONC::Type (Value::Type::Document, i)
{
   const bson_uint8_t * buf;
   bson_uint32_t len;

   bson_iter_document(t, &len, &buf);

   bson_init_static(&child, buf, len);
}

void
BSONC::Type::Doc::print (std::ostream & stream) const
{
   char *str = bson_as_json (&child, NULL);

   stream << str;

   free (str);
}
}
