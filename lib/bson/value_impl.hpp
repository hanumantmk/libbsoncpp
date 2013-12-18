#ifndef BSONCPP_VALUE_IMPL_H
#define BSONCPP_VALUE_IMPL_H

#include "bson/value.hpp"

namespace BSON {

class Document;

class ValueImpl {
protected:
   virtual void magicSizeGuard(Value v) const = 0;

public:
   virtual ValueType get_type () const = 0;

   virtual ~ValueImpl()
   {
   };

   virtual ValueImpl * clone(ValueImpl * storage) const = 0;

   virtual const char * to_utf8() const;
   virtual int32_t to_int32() const;
   virtual std::tuple<const uint8_t *, size_t> to_bson() const;

   virtual Value operator [] (const char * s) const;
   virtual Value operator [] (int i) const;

   virtual Document & to_document();

   virtual ValueIterator begin() const;
   virtual ValueIterator end() const;

   virtual void
   print (std::ostream & stream) const
   {
   }
};

}

std::ostream & operator << (std::ostream & out, const BSON::ValueImpl &obj);

#endif
