#ifndef BSONCPP_BSONC_H
#define BSONCPP_BSONC_H

#include "bson_document.hpp"
#include <functional>

extern "C" {
#include <bson.h>
}

namespace BSON {

class BSONC : public Document {
private:
   class AppendCtx
   {
      bson_t *root;
      
      struct {
         bson_t bson;
         int lastKey;
         bool is_array;
      } stack[30];

      int depth = -1;
      char lastKeyBuf[30];

   public:
      AppendCtx(bson_t *b);
      const char * nextKey ();
      bson_t *top();
      bson_t *push(const char * key, bool is_array);
      void pop();
   };

   typedef std::function<void(AppendCtx &ctx, const char * key, BSONC &b)> args_t;

private:
   std::shared_ptr<bson_t> bson;

public:
   class Type;

   BSONC(Value::Type t);

   BSONC(Value::Type t, const std::shared_ptr<bson_t> &b);

   void clone(Impl * storage) const;

   template <class ...T>
   BSONC(const T& ...t) : BSONC(Value::Type::Root)
   {
      AppendCtx ctx(bson.get());

      append_doc (ctx, t...);
   }

   template <class ...T>
   static args_t Array(const T& ...t)
   {
      return [&](AppendCtx &ctx, const char * key, BSONC &b) {
         ctx.push(key, true);
         b.append_array (ctx, t...);
         ctx.pop();
      };
   }

   template <class ...T>
   static args_t Doc(const T& ...t)
   {
      return [&](AppendCtx &ctx, const char * key, BSONC &b) {
         ctx.push(key, false);
         b.append_doc (ctx, t...);
         ctx.pop();
      };
   }

   void
   toBson (void  **buf,
           size_t *len) const;

   void
   append_single (AppendCtx &ctx, const char * key,
                  int32_t     i);

   void
   append_single (AppendCtx &ctx, const char * key,
                  const char * val);

   void
   append_single (AppendCtx &ctx, const char * key,
                  const Document &b);

   void
   append_single (AppendCtx &ctx, const char * key,
                  args_t args);

   void
   print(std::ostream & stream) const;

   Value operator [] (const char * s) const;

   template <class T>
   void append_doc (AppendCtx &ctx, const char * key, const T& t)
   {
      append_single (ctx, key, t);
   }

   template <class Arg1, class ...ArgN>
   void append_doc(AppendCtx &ctx, const char * key, const Arg1& a1, const ArgN& ...an)
   {
      append_single (ctx, key, a1);
      append_doc (ctx, an...);
   }

   template <class T>
   void append_array (AppendCtx &ctx, const T& t)
   {
      append_single (ctx, ctx.nextKey(), t);
   }

   template <class Arg1, class ...ArgN>
   void append_array(AppendCtx &ctx,  const Arg1& a1, const ArgN& ...an)
   {
      append_single (ctx, ctx.nextKey(), a1);
      append_array (ctx, an...);
   }

   BSONCPP_VALUE_GUARD(BSONC)
};

}

#endif
