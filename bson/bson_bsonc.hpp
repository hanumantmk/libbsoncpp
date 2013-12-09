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
   friend class BSONCUtils;
   class Impl;
   class Type;

   class Token {
   public:
      class Array {
      public:
         Array() {}
      };
      class Doc {
      public:
         Doc() {}
      };
      class End {
      public:
         End() {}
      };
   };

   typedef std::function<void( const char * key, BSONC &b)> args_t;

private:
   BSONC(Value::Type t, const std::shared_ptr<Impl> &i);
   std::shared_ptr<Impl> impl;

void push(const char * key, bool is_array);
void pop();
const char * nextKey();
bool is_array();

public:
   BSONC();
   BSONC(Value::Type t);

   void clone(Value::Impl * storage) const;

   template <class ...T>
   BSONC(const T& ...t) : BSONC(Value::Type::Root)
   {
      append_doc (t...);
   }

   static Token::Array TArray()
   {
      return Token::Array();
   }

   static Token::Doc TDoc()
   {
      return Token::Doc();
   }

   static Token::End TEnd()
   {
      return Token::End();
   }

   template <class ...T>
   static args_t Array(const T& ...t)
   {
      return [&]( const char * key, BSONC &b) {
         b.push(key, true);
         b.append_array (t...);
         b.pop();
      };
   }

   template <class ...T>
   static args_t Doc(const T& ...t)
   {
      return [&]( const char * key, BSONC &b) {
         b.push(key, false);
         b.append_doc (t...);
         b.pop();
      };
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
   append_single ( const char * key,
                  args_t args);

   void
   append_single ( const char * key,
                   const Token::Array & t);

   void
   append_single ( const char * key,
                   const Token::Doc & t);

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
   void append_doc( const char * key, const Token::Array& a, const ArgN& ...an)
   {
      append_single (key, a);

      append_array (an...);
   }

   template <class ...ArgN>
   void append_doc( const Token::End & e, const ArgN& ...an)
   {
      pop();
      if (is_array()) {
         append_array (an...);
      } else {
         append_doc (an...);
      }
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
   void append_array( const Token::Doc &d,  const ArgN& ...an)
   {
      append_single (nextKey(), d);
      append_doc (an...);
   }

   template <class ...ArgN>
   void append_array ( const Token::End & e, const ArgN& ...an)
   {
      pop();
      if (is_array()) {
         append_array (an...);
      } else {
         append_doc (an...);
      }
   }

   BSONCPP_VALUE_GUARD(BSONC)
};

}

#endif
