#ifndef BSONCPP_DOCUMENT_H
#define BSONCPP_DOCUMENT_H

#include "bson_value_impl.hpp"
#include <unistd.h>
#include <cstdint>
#include <string>
#include <ostream>

namespace BSON {

class Document : public Value::Impl {
public:
   Document(Value::Type t) : Impl(t) {}

   virtual void
   toBson (void  **buf,
           size_t *len) const = 0;

   virtual void
   append_single (const char * key,
                  int32_t     i) = 0;

   virtual void
   append_single (const char *key,
                  const char *s) = 0;

   virtual void
   append_single (const char * key,
                  const Document &b) = 0;

   virtual Value operator [] (const char * s) const = 0;

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
};

}

#endif
