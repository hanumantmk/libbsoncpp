#include "bson_bsonc_utf8.hpp"

namespace BSON {
BSONC::Type::UTF8::UTF8 (const std::shared_ptr<BSONC::Impl> &i,
                   const char                    *v) :
   BSONC::Type (Value::Type::UTF8, i),
   val (v)
{
}

void
BSONC::Type::UTF8::print (std::ostream & stream) const
{
   stream << val;
}

void BSONC::Type::UTF8::clone(Value::Impl * storage) const
{
   new (storage) BSONC::Type::UTF8(impl, val);
}

const char * BSONC::Type::UTF8::to_utf8() const
{
   return val;
}

}
