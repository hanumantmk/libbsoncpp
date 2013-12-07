#include "bson_bsonc.hpp"

namespace BSON {

BSONC::AppendCtx::AppendCtx(bson_t *b) :
   root(b)
{
}

const char * BSONC::AppendCtx::nextKey ()
{
   sprintf(lastKeyBuf, "%d", stack[depth].lastKey++);
   return (lastKeyBuf);
}

bson_t * BSONC::AppendCtx::top()
{
   if (depth >= 0) {
      return &(stack[depth].bson);
   } else {
      return root;
   }
}

bson_t * BSONC::AppendCtx::push(const char * key, bool is_array)
{
   bson_t *child = &(stack[depth + 1].bson);

   if (is_array) {
      bson_append_array_begin(top(), key, -1, child);
   } else {
      bson_append_document_begin(top(), key, -1, child);
   }

   depth++;

   stack[depth].lastKey = 0;
   stack[depth].is_array = is_array;

   return top();
}

void BSONC::AppendCtx::pop()
{
   bson_t *child = top();
   depth--;

   if (stack[depth + 1].is_array) {
      bson_append_array_end(top(), child);
   } else {
      bson_append_document_end(top(), child);
   }
}

}
