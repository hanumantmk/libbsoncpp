#ifndef BSONCPP_VALUE_IMPL_H
#define BSONCPP_VALUE_IMPL_H

#include "bson/value.hpp"

namespace BSON {

class Document;

class Value::Impl {
protected:
   virtual void magicSizeGuard(Value v) const = 0;

public:
   virtual Type get_type () const = 0;

   virtual ~Impl()
   {
   };

   virtual Impl * clone(Impl * storage) const = 0;

   virtual const char * to_utf8() const;
   virtual int32_t to_int32() const;
   virtual std::tuple<const uint8_t *, size_t> to_bson() const;

   virtual Value operator [] (const char * s) const;
   virtual Value operator [] (int i) const;

   virtual BSON::Document & to_document();

   virtual Iterator begin() const;
   virtual Iterator end() const;

   virtual void
   print (std::ostream & stream) const
   {
   }
};

}

std::ostream & operator << (std::ostream & out, const BSON::Value::Impl &obj);

#endif
