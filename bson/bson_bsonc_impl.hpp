#ifndef BSONCPP_BSONC_IMPL_H
#define BSONCPP_BSONC_IMPL_H

#include "bson_bsonc.hpp"
#include <stack>

namespace BSON {

class BSONC::Impl {
   class AppendLayer {
   public:
      bson_t bson;
      bson_t *parent = NULL;
      int lastKey = 0;
      bool is_array;

      AppendLayer(bson_t * parent, const char * key, bool is_array);
      ~AppendLayer();
   };

   bson_t root;
   std::stack<AppendLayer> stack;
   char lastKeyBuf[30];

public:
   Impl();
   ~Impl();

   const char * nextKey ();
   bson_t *top();
   bson_t *push(const char * key, bool is_array);
   void pop();
};

}

#endif
