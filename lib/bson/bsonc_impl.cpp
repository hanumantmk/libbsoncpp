#include "bson/bsonc_impl.hpp"

namespace BSON {

BSONC::Impl::Impl() :
   is_static(false)
{
   bson_init(&root);
}

BSONC::Impl::Impl(const std::tuple<const uint8_t *, uint32_t> & bson) :
   is_static(true)
{
   bson_init_static(&root, std::get<0>(bson), std::get<1>(bson));
}

BSONC::Impl::~Impl()
{
   if (! is_static) {
      bson_destroy(&root);
   }
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
