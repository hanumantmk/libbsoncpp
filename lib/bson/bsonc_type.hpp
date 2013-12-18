#ifndef BSONCPP_BSONC_TYPE_H
#define BSONCPP_BSONC_TYPE_H

#include "bson/bsonc.hpp"
#include "bson/bsonc_impl.hpp"
#include "bson/types.hpp"
#include "bson/value_impl.hpp"
#include "bson/iterator_impl.hpp"

namespace BSON {

class BSONCType :
   public ValueImpl,
   public ValueIteratorImpl
{
   const bson_t * impl;

   size_t bson_offset;
   size_t bson_len;

   size_t iter_offset;

   bool is_root;
private:
   bool init_iter(bson_t *bson, bson_iter_t *iter) const;

public:
   BSONCType (const bson_t * b);
   BSONCType (const bson_t * b, const bson_iter_t * iter);

   ValueType get_type() const;

   ValueImpl * clone(ValueImpl * storage) const;
   ValueIteratorImpl * clone(ValueIteratorImpl * storage) const;

   const char * to_utf8() const;

   int32_t to_int32() const;

   std::tuple<const uint8_t *, size_t> to_bson() const;

   Value operator [] (int i) const;
   Value operator [] (const char * s) const;

   ValueIterator begin() const;
   ValueIterator end() const;

   void print (std::ostream & stream) const;

   void next();

   bool is_end() const;

   bool is_equal(const ValueIteratorImpl &other) const;

   const char *
   key() const;

   Value
   to_value() const;

   BSONCPP_VALUE_GUARD;
   BSONCPP_VALUE_ITERATOR_GUARD;
};


}

#endif
