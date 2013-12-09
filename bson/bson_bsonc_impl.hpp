#ifndef BSONCPP_BSONC_IMPL_H
#define BSONCPP_BSONC_IMPL_H

#include "bson_bsonc.hpp"

namespace BSON {

class BSONC::Impl {
   class AppendLayer {
   public:
      bson_t bson;
      bson_t *parent = NULL;
      int lastKey = 0;
      bool is_array;

      AppendLayer();
      AppendLayer(bson_t * parent, const char * key, bool is_array);
      ~AppendLayer();
   };

   bson_t root;
   std::aligned_storage<sizeof(AppendLayer), alignof(AppendLayer)>::type stack[30];
   int depth = -1;
   char lastKeyBuf[30];
   AppendLayer * _top(int offset);

public:
   Impl();
   ~Impl();

   const char * nextKey ();
   bson_t *top();
   bool is_array();
   bson_t *push(const char * key, bool is_array);
   void pop();
};

}

#endif
