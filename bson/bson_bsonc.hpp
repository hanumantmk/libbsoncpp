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
   typedef std::function<void(const char * key, BSONC &b)> args_t;

private:
   std::shared_ptr<bson_t> bson;
   bson_t *append_ctx;
   int lastKey = 0;
   char lastKeyBuf[10];
   const char * nextKey ();

public:
   class Type;

   BSONC(Value::Type t);

   BSONC(Value::Type t, const std::shared_ptr<bson_t> &b);

   void clone(Impl * storage) const;

   template <class ...T>
   BSONC(const T& ...t) : BSONC(Value::Type::Root)
   {
      append_doc (t...);
   }

   template <class ...T>
   static args_t Array(const T& ...t)
   {
      return [&](const char * key, BSONC &b) {
         bson_t child;
         bson_t *old = b.append_ctx;
         bson_append_array_begin(b.append_ctx, key, -1, &child);

         b.append_ctx = &child;
         b.append_array (t...);
         b.append_ctx = old;

         bson_append_array_end(b.append_ctx, &child);
      };
   }

   template <class ...T>
   static args_t Doc(const T& ...t)
   {
      return [&](const char * key, BSONC &b) {
         bson_t child;
         bson_t *old = b.append_ctx;
         bson_append_document_begin(b.bson.get(), key, -1, &child);

         b.append_ctx = &child;
         b.append_doc (t...);
         b.append_ctx = old;

         bson_append_document_end(b.append_ctx, &child);
      };
   }

   void
   toBson (void  **buf,
           size_t *len) const;

   void
   append_single (const char * key,
                  int32_t     i);

   void
   append_single (const char * key,
                  const char * val);

   void
   append_single (const char * key,
                  const Document &b);

   void
   append_single (const char * key,
                  args_t args);

   void
   print(std::ostream & stream) const;

   Value operator [] (const char * s) const;

   template <class T>
   void append_doc (const char * key, const T& t)
   {
      append_single (key, t);
   }

   template <class Arg1, class ...ArgN>
   void append_doc(const char * key, const Arg1& a1, const ArgN& ...an)
   {
      append_single (key, a1);
      append_doc (an...);
   }

   template <class T>
   void append_array (const T& t)
   {
      append_single (nextKey(), t);
   }

   template <class Arg1, class ...ArgN>
   void append_array( const Arg1& a1, const ArgN& ...an)
   {
      append_single (nextKey(), a1);
      append_array (an...);
   }

   BSONCPP_VALUE_GUARD(BSONC)
};

}

#endif
