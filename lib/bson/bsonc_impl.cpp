#include "bson/bsonc_impl.hpp"

namespace BSON {

BSONCImpl::BSONCImpl() :
   is_static(false)
{
   bson_init(&root);
}

BSONCImpl::~BSONCImpl()
{
   if (! is_static) {
      bson_destroy(&root);
   }
}

const char * BSONCImpl::nextKey ()
{
   sprintf(lastKeyBuf, "%d", storage.top().lastKey++);
   return (lastKeyBuf);
}

bson_t * BSONCImpl::bottom()
{
   return &root;
}

bson_t * BSONCImpl::top()
{
   if (storage.empty()) {
      return &root;
   } else {
      return &storage.top().bson;
   }
}

bson_t * BSONCImpl::push(const char * key, bool is_array)
{
   storage.emplace(top(), key, is_array);

   return top();
}

bool BSONCImpl::is_array()
{
   if (storage.empty()) {
      return false;
   } else {
      return storage.top().is_array;
   }
}

void BSONCImpl::pop()
{
   storage.pop();
}

}
