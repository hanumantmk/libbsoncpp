#ifndef BSONCPP_BSONC_H
#define BSONCPP_BSONC_H

#include "bson_document.hpp"

extern "C" {
#include <bson.h>
}

namespace BSON {

class BSONC : public Document {
private:
   class UTF8;

private:
   std::shared_ptr<bson_t> bson;
   int lastKey = 0;

protected:
   virtual std::string nextKey ();

public:
   BSONC(Value::Type t);

   template <class ...T>
   BSONC(const T& ...t) : BSONC(Value::Type::Root)
   {
      append_doc (t...);
   }

   template <class ...T>
   static BSONC Array(const T& ...t)
   {
      BSONC b = BSONC(Value::Type::Array);
      b.append_array (t...);
      return b;
   }

   virtual void
   toBson (void  **buf,
           size_t *len) const;

   virtual void
   append_single (const std::string & key,
                  int32_t     i);

   virtual void
   append_single (const std::string & key,
                  const std::string & s);

   virtual void
   append_single (const std::string & key,
                  const Document &b);

   virtual void
   print(std::ostream & stream) const;

   virtual Value operator [] (const std::string & s);
};

}

#endif
