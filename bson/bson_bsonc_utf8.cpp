#include "bson_bsonc_utf8.hpp"

namespace BSON {
BSONC::UTF8::UTF8 (const std::shared_ptr<bson_t> &i,
                   const char                    *v) :
   Value::Impl (Value::Type::UTF8),
   bson (i),
   val (v)
{
}

void
BSONC::UTF8::print (std::ostream & stream) const
{
   stream << val;
}
}
