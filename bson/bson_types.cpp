#include "bson_types.hpp"

namespace BSON {

namespace Types {
Type Int32(int32_t i) {
   return Type::Int32(i);
}

Type Utf8(const char * utf8) {
   return Type::Utf8(utf8);
}

Type Null() {
   return Type::Null();
}

Type Array(const uint8_t *buf, size_t len) {
   return Type::Array(buf, len);
}

Type Document(const uint8_t *buf, size_t len) {
   return Type::Document(buf, len);
}
}

}
