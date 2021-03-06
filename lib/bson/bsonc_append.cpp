#include "bson/bsonc_impl.hpp"

namespace BSON {

BSONCImpl::AppendLayer::AppendLayer(bson_t *parent, const Key & key, bool is_array) :
   parent(parent),
   is_array(is_array)
{
   if (is_array) {
      bson_append_array_begin(parent, key.c_str(), key.length(), &bson);
   } else {
      bson_append_document_begin(parent, key.c_str(), key.length(), &bson);
   }
}

BSONCImpl::AppendLayer::~AppendLayer()
{
   if (is_array) {
      bson_append_array_end(parent, &bson);
   } else {
      bson_append_document_end(parent, &bson);
   }
}

}
