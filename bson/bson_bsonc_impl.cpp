#include "bson_bsonc_impl.hpp"

namespace BSON {

BSONC::Impl::Impl()
{
   bson_init(&root);
}

BSONC::Impl::~Impl()
{
   while(! stack.empty()) {
      pop();
   }

   bson_destroy(&root);
}

const char * BSONC::Impl::nextKey ()
{
   sprintf(lastKeyBuf, "%d", stack.top().lastKey++);
   return (lastKeyBuf);
}

bson_t * BSONC::Impl::top()
{
   if (stack.empty()) {
      return &root;
   } else {
      return &stack.top().bson;
   }
}

bson_t * BSONC::Impl::push(const char * key, bool is_array)
{
   stack.emplace( top(), key, is_array);

   return top();
}

void BSONC::Impl::pop()
{
   stack.pop();
}

}
