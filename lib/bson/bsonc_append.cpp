#include "bson/bsonc_impl.hpp"

namespace BSON {

BSONC::Impl::AppendLayer::AppendLayer()
{
}

BSONC::Impl::AppendLayer::AppendLayer(bson_t *parent, const char * key, bool is_array) :
   parent(parent),
   is_array(is_array)
{
   if (is_array) {
      bson_append_array_begin(parent, key, -1, &bson);
   } else {
      bson_append_document_begin(parent, key, -1, &bson);
   }
}

BSONC::Impl::AppendLayer::~AppendLayer()
{
   if (is_array) {
      bson_append_array_end(parent, &bson);
   } else {
      bson_append_document_end(parent, &bson);
   }
}

}
