#ifndef BSONCPP_DOCUMENT_H
#define BSONCPP_DOCUMENT_H

#include "bson_value_impl.hpp"
#include <unistd.h>
#include <cstdint>
#include <string>
#include <ostream>

namespace BSON {

class Document : public Value::Impl {
private:
   void pop(bool arr) {
      if (! in_progress()) {
         throwArgs("", "Attempting to close the root document");
      }

      if (arr != is_array()) {
         throwArgs("", "mismatched sub document close");
      }

      pop();
   }

protected:
   virtual void push(const char * key, bool is_array) = 0;
   virtual void pop() = 0;
   virtual bool in_progress() = 0;
   virtual const char * nextKey() = 0;
   virtual bool is_array() = 0;
   virtual void throwArgs(const char * key, const char * msg) = 0;
public:
   virtual std::tuple<const uint8_t *, size_t> to_bson() const = 0;
   virtual void append_single ( const char * key, const Value &v) = 0;

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
   Document & append (  const ArgN& ...an)
   {
      if (is_array()) {
         append_array (an...);
      } else {
         append_doc (an...);
      }

      return *this;
   }
};

}

#endif
