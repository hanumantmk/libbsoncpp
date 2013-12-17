#ifndef BSONCPP_BSONC_H
#define BSONCPP_BSONC_H

#include "bson/document.hpp"

namespace BSON {

class BSONC : public Document {
private:
   friend class BSONCUtils;
   class Impl;
   class Type;
   class Iterator;

   friend class Type;
   friend class Iterator;

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
   BSONC(const std::tuple<const uint8_t *, uint32_t> & bson);

   Value::Type get_type () const;
   auto clone(Value::Impl * storage) const -> Value::Impl *;

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

   Value::Iterator begin() const;

   Value::Iterator end() const;

   BSONCPP_VALUE_GUARD
};

}

#endif
