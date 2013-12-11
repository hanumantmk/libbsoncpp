#include "bson_bsonc_impl.hpp"

namespace BSON {

BSONC::Impl::Impl()
{
   bson_init(&root);
}

BSONC::Impl::~Impl()
{
   bson_destroy(&root);
}

const char * BSONC::Impl::nextKey ()
{
   sprintf(lastKeyBuf, "%d", storage.top().lastKey++);
   return (lastKeyBuf);
}

bson_t * BSONC::Impl::bottom()
{
   return &root;
}

bson_t * BSONC::Impl::top()
{
   if (storage.empty()) {
      return &root;
   } else {
      return &storage.top().bson;
   }
}

bson_t * BSONC::Impl::push(const char * key, bool is_array)
{
   storage.emplace(top(), key, is_array);

   return top();
}

bool BSONC::Impl::is_array()
{
   if (storage.empty()) {
      return false;
   } else {
      return storage.top().is_array;
   }
}

void BSONC::Impl::pop()
{
   storage.pop();
}

}