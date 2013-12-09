#include "bson_bsonc_type.hpp"

namespace BSON {

BSONC::Type::Type (Value::Type t, const std::shared_ptr<BSONC::Impl> &i) :
   Value::Impl(t),
   impl(i)
{
}

}
