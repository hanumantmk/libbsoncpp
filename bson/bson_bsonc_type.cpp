#include "bson_bsonc_type.hpp"

namespace BSON {

BSONC::Type::Type (Value::Type t, const std::shared_ptr<bson_t> &b) :
   Value::Impl(t),
   bson(b)
{
}

}
