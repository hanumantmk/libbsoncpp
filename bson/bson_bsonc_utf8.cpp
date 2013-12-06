#include "bson_bsonc_utf8.hpp"

namespace BSON {
BSONC::Type::UTF8::UTF8 (const std::shared_ptr<bson_t> &i,
                   const char                    *v) :
   BSONC::Type (Value::Type::UTF8, i),
   val (v)
{
   static_assert(sizeof(UTF8) <= Value::storage_size, "BSONC::Type::UTF8 too large to fit in Value");
}

void
BSONC::Type::UTF8::print (std::ostream & stream) const
{
   stream << val;
}

void BSONC::Type::UTF8::clone(Value::Impl * storage) const
{
   new (storage) BSONC::Type::UTF8(bson, val);
}

}
