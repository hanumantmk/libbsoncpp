#ifndef BSONCPP_BSONC_H
#define BSONCPP_BSONC_H

#include "bson_document.hpp"

extern "C" {
#include <bson.h>
}

namespace BSON {

class BSONC : public Document {
private:
   friend class BSONCUtils;
   class Impl;

   template <Value::Type t>
   class Type;

   class Types {
      public:
      class Doc;
      class Array;
      class UTF8;
   };

private:
   BSONC(const std::shared_ptr<Impl> &i);
   std::shared_ptr<Impl> impl;

   void push(const char * key, bool is_array);
   void pop(bool is_array);
   const char * nextKey();
   bool is_array();
   void throwArgs(const char * key, const char * msg);

public:
   BSONC();

   Value::Type get_type () const;
   void clone(Value::Impl * storage) const;

   template <class ...T>
   BSONC(const T& ...t) : BSONC()
   {
      append_doc (t...);
   }

   void
   toBson (void  **buf,
           size_t *len) const;

   void
   append_single ( const char * key,
                  int32_t     i);

   void
   append_single ( const char * key,
                  const char * val);

   void
   append_single ( const char * key,
                  const Document &b);

   void
   print(std::ostream & stream) const;

   Value operator [] (const char * s) const;

   template <class T>
   void append_doc ( const char * key, const T& t)
   {
      append_single (key, t);
   }

   template <class Arg1, class ...ArgN>
   void append_doc( const char * key, const Arg1& a1, const ArgN& ...an)
   {
      append_single (key, a1);
      append_doc (an...);
   }

   template <class ...ArgN>
   void append_doc( const char * key, char a, const ArgN& ...an)
   {
      if (!(a == '{' || a == '[')) {
         throwArgs(key, "document control characters restricted to [{[] for values");
      }

      push(key, a == '[');
      append(an...);
   }

   void append_doc( char a )
   {
      if (!(a == '}' || a == ']')) {
         throwArgs("", "document control characters restricted to [}]] for keys");
      }

      pop(a == ']');
   }

   template <class ...ArgN>
   void append_doc( char c, const ArgN& ...an)
   {
      append_doc(c);

      append(an...);
   }

   template <class T>
   void append_array ( const T& t)
   {
      append_single (nextKey(), t);
   }

   template <class Arg1, class ...ArgN>
   void append_array(  const Arg1& a1, const ArgN& ...an)
   {
      append_single (nextKey(), a1);
      append_array (an...);
   }

   template <class ...ArgN>
   void append_array( char a, const ArgN& ...an)
   {
      append_array(a);

      append( an...);
   }

   void append_array( char a)
   {
      if (!(a == '{' || a == '}' || a == '[' || a == ']')) {
         throwArgs(nextKey(), "array control characters restricted to [{}[]]");
      }

      if (a == '{' || a == '[') {
         push(nextKey(), a == '[');
      } else {
         pop(a == ']');
      }
   }

   template <class ...ArgN>
   BSONC & append (  const ArgN& ...an)
   {
      if (is_array()) {
         append_array (an...);
      } else {
         append_doc (an...);
      }

      return *this;
   }

   BSONCPP_VALUE_GUARD(BSONC)
};

}

#endif
