#ifndef BSONCPP_BSONC_TYPE_H
#define BSONCPP_BSONC_TYPE_H

#include "bson_bsonc.hpp"
#include "bson_bsonc_impl.hpp"
#include "bson_types.hpp"
#include "bson_value_impl.hpp"
#include "bson_iterator_impl.hpp"

namespace BSON {

class BSONC::Type :
   public Value::Impl,
   public Value::Iterator::Impl
{
   std::shared_ptr<BSONC::Impl> impl;

   size_t bson_offset;
   size_t bson_len;

   size_t iter_offset;
private:
   bool init_iter(bson_t *bson, bson_iter_t *iter) const;

public:
   Type (const std::shared_ptr<BSONC::Impl> &b, const bson_iter_t * iter);

   Value::Type get_type() const;

   Value::Impl * clone(Value::Impl * storage) const;
   Value::Iterator::Impl * clone(Value::Iterator::Impl * storage) const;

   const char * to_utf8() const;

   int32_t to_int32() const;

   std::tuple<const uint8_t *, size_t> to_bson() const;

   Value operator [] (int i) const;
   Value operator [] (const char * s) const;

   Value::Iterator begin() const;
   Value::Iterator end() const;

   void print (std::ostream & stream) const;

   void next();

   bool is_end() const;

   bool is_equal(const Value::Iterator::Impl &other) const;

   const char *
   key() const;

   Value
   to_value() const;

   BSONCPP_VALUE_GUARD;
   BSONCPP_VALUE_ITERATOR_GUARD;
};


}

#endif
