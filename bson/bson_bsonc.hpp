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

protected:
   void push(const char * key, bool is_array);
   void pop();
   bool in_progress();
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

   std::tuple<const uint8_t *, size_t> to_bson() const;

   void
   append_single ( const char * key,
                  const Value &v);

   void
   print(std::ostream & stream) const;

   Value operator [] (const char * s) const;

   BSONCPP_VALUE_GUARD
};

}

#endif
