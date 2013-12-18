#ifndef BSONCPP_BSONC_IMPL_H
#define BSONCPP_BSONC_IMPL_H

#include "bson/stack.hpp"

extern "C" {
#include <bson.h>
}

namespace BSON {

class BSONCImpl {
   class AppendLayer {
   public:
      bson_t bson;
      bson_t *parent = nullptr;
      int lastKey = 0;
      bool is_array;

      AppendLayer(bson_t * parent, const std::string & key, bool is_array);
      ~AppendLayer();
   };

   Stack<AppendLayer, 4> storage;

   uint8_t *buf_ptr;
   size_t buf_len;

   bson_writer_t * writer;

   bson_t * root;

   char lastKeyBuf[30];

public:
   BSONCImpl();
   ~BSONCImpl();

   void clear();

   const char * nextKey ();
   bson_t *bottom();
   bson_t *top();
   bool is_array();
   bson_t *push(const std::string & key, bool is_array);
   void pop();
};

}

#endif
