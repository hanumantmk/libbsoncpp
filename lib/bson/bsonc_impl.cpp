#include "bson/bsonc_impl.hpp"

namespace BSON {

BSONCImpl::BSONCImpl() :
   buf_ptr((uint8_t *)malloc(256)),
   buf_len(256),
   writer(bson_writer_new(&buf_ptr, &buf_len, 0, &realloc)),
   key("0", 1)
{
   bson_writer_begin(writer, &root);
}

BSONCImpl::~BSONCImpl()
{
   bson_writer_destroy(writer);
   free(buf_ptr);
}

void BSONCImpl::clear()
{
   while (! storage.empty()) {
      storage.pop();
   }

   bson_writer_rollback(writer);
   bson_writer_begin(writer, &root);
}

const Key & BSONCImpl::nextKey ()
{
   int i;
   
   i = sprintf(lastKeyBuf, "%d", storage.top().lastKey++);
   key = Key(lastKeyBuf, i);

   return key;
}

bson_t * BSONCImpl::bottom()
{
   return root;
}

bson_t * BSONCImpl::top()
{
   if (storage.empty()) {
      return root;
   } else {
      return &storage.top().bson;
   }
}

bson_t * BSONCImpl::push(const Key & key, bool is_array)
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
