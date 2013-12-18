#ifndef BSONCPP_BSONC_H
#define BSONCPP_BSONC_H

#include "bson/document.hpp"

namespace BSON {

class BSONCImpl;

class BSONC : public Document {
public:
   class Type;

private:
   friend class BSONCUtils;

   friend class Type;
   friend class Iterator;

private:
   BSONC(const std::shared_ptr<BSONCImpl> &i);
   std::shared_ptr<BSONCImpl> impl;

protected:
   void push(const char * key, bool is_array);
   void pop();
   bool in_progress();
   const char * nextKey();
   bool is_array();
   void throwArgs(const char * key, const char * msg);

public:
   BSONC();

   ValueType get_type () const;
   auto clone(ValueImpl * storage) const -> ValueImpl *;

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

   Document & to_document();

   ValueIterator begin() const;

   ValueIterator end() const;

   BSONCPP_VALUE_GUARD
};

}

#endif
