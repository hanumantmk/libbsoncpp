#ifndef BSONCPP_BSONC_APPEND_H
#define BSONCPP_BSONC_APPEND_H

extern "C" {
#include <bson.h>
}

namespace BSON {

class AppendCtx
{
   bson_t *bson[100];
   int depth = 0;
   int lastKey = 0;
   char lastKeyBuf[30];

public:
   AppendCtx(bson_t *b);
   const char * nextKey ();
   bson_t *top();
   void push(bson_t *b);
   void pop();
};

}

#endif
