#ifndef BSONCPP_BSONC_IMPL_H
#define BSONCPP_BSONC_IMPL_H

#include "bson/bsonc.hpp"
#include "bson/stack.hpp"

extern "C" {
#include <bson.h>
}

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

   Stack<AppendLayer, 4> storage;

   bson_t root;

   char lastKeyBuf[30];

   bool is_static;

public:
   Impl();
   ~Impl();

   const char * nextKey ();
   bson_t *bottom();
   bson_t *top();
   bool is_array();
   bson_t *push(const char * key, bool is_array);
   void pop();
};

}

#endif
