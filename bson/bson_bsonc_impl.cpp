#include "bson_bsonc_impl.hpp"

namespace BSON {

BSONC::Impl::Impl()
{
   bson_init(&root);
}

BSONC::Impl::~Impl()
{
   while(depth >= 0) {
      pop();
   }

   bson_destroy(&root);
}

BSONC::Impl::AppendLayer * BSONC::Impl::_top(int offset = 0)
{
   return static_cast<BSONC::Impl::AppendLayer *>(static_cast<void *>(&stack[depth + offset]));
}

const char * BSONC::Impl::nextKey ()
{
   sprintf(lastKeyBuf, "%d", _top()->lastKey++);
   return (lastKeyBuf);
}

bson_t * BSONC::Impl::top()
{
   if (depth < 0) {
      return &root;
   } else {
      return &_top()->bson;
   }
}

bson_t * BSONC::Impl::push(const char * key, bool is_array)
{
   new (_top(1)) AppendLayer( top(), key, is_array);

   depth++;

   return top();
}

bool BSONC::Impl::is_array()
{
   if (depth < 0) {
      return false;
   } else {
      return _top()->is_array;
   }
}

void BSONC::Impl::pop()
{
   _top()->~AppendLayer();
   depth--;
}

}
