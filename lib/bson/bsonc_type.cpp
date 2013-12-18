#include "bson/bsonc_type.hpp"
#include "bson/bsonc_utils.hpp"
#include "bson/iterator.hpp"
#include "bson/bsonc_impl.hpp"

namespace BSON {

BSONCType::BSONCType (const bson_t *b, const bson_iter_t * iter) :
   impl(b),
   bson_offset(bson_get_data(iter->bson) - bson_get_data(b)),
   bson_len(iter->bson->len),
   iter_offset(iter->offset),
   is_root(false)
{
}

BSONCType::BSONCType (const bson_t *b) :
   impl(b),
   bson_offset(0),
   bson_len(b->len),
   iter_offset(0),
   is_root(true)
{
}

bool BSONCType::init_iter(bson_t *bson, bson_iter_t *iter) const {
   bson_init_static(bson, bson_get_data(impl) + bson_offset, bson_len);
   bson_iter_init(iter, bson);

   if (is_root) {
      return true;
   } else {
      iter->next_offset = iter_offset;
      return bson_iter_next(iter);
   }
}

ValueType BSONCType::get_type() const
{
   bson_t bson;
   bson_iter_t iter;

   if (is_root) {
      return ValueType::Document;
   } else {
      init_iter(&bson, &iter);

      return (ValueType)bson_iter_type(&iter);
   }
}

ValueImpl * BSONCType::clone(ValueImpl * storage) const
{
   bson_t bson;
   bson_iter_t iter;

   if (is_root) {
      return new (storage) BSONCType(impl);
   } else {
      init_iter(&bson, &iter);

      return new (storage) BSONCType(impl, &iter);
   }
}

ValueIteratorImpl * BSONCType::clone(ValueIteratorImpl * storage) const
{
   bson_t bson;
   bson_iter_t iter;

   if (is_root) {
      return new (storage) BSONCType(impl);
   } else {
      init_iter(&bson, &iter);

      return new (storage) BSONCType(impl, &iter);
   }
}

const char * BSONCType::to_utf8() const {
   bson_t bson;
   bson_iter_t iter;

   init_iter(&bson, &iter);

   return bson_iter_utf8(&iter, nullptr);
}

int32_t BSONCType::to_int32() const {
   bson_t bson;
   bson_iter_t iter;

   init_iter(&bson, &iter);

   return bson_iter_int32(&iter);
}

std::tuple<const uint8_t *, size_t> BSONCType::to_bson() const
{
   bson_t bson;
   bson_iter_t iter;
   const uint8_t *buf;
   uint32_t len;

   if (is_root) {
      buf = bson_get_data(impl);
      len = impl->len;
   } else {
      init_iter(&bson, &iter);

      if (get_type() == ValueType::Document) {
         bson_iter_document(&iter, &len, &buf);
      } else {
         bson_iter_array(&iter, &len, &buf);
      }
   }

   return std::make_tuple(buf, len);
}

void
BSONCType::print (std::ostream & stream) const
{
   bson_t bson;
   bson_iter_t iter;
   init_iter(&bson, &iter);

   if (is_root) {
      BSONCUtils::pp( stream, &iter, 0, false );
   } else {
      BSONCUtils::pp_type( stream, &iter, 0 );
   }
}

Value
BSONCType::operator [] (int i) const
{
   const uint8_t *buf;
   size_t len;
   bson_t child;

   std::tie(buf, len) = to_bson();

   bson_init_static(&child, buf, len);

   char str[30];
   sprintf(str, "%d", i);

   return BSONCUtils::convert(impl, &child, str);
}

Value
BSONCType::operator [] (const char * str) const
{
   const uint8_t *buf;
   size_t len;
   bson_t child;

   std::tie(buf, len) = to_bson();

   bson_init_static(&child, buf, len);

   return BSONCUtils::convert(impl, &child, str);
}

ValueIterator BSONCType::begin() const
{
   bson_t bson;
   bson_iter_t iter;

   init_iter(&bson, &iter);

   if (! iter_offset) {
      bson_iter_next(&iter);
   }

   return ValueIterator(BSONCType(impl, &iter));
}

ValueIterator BSONCType::end() const
{
   return ValueIteratorEnd();
}

void BSONCType::next()
{
   bson_t bson;
   bson_iter_t iter;

   init_iter(&bson, &iter);

   bson_iter_next(&iter);

   iter_offset = iter.offset;
}

bool BSONCType::is_end() const
{
   bson_t bson;
   bson_iter_t iter;
   return init_iter(&bson, &iter);
}

bool BSONCType::is_equal(const ValueIteratorImpl &other) const
{
   if (is_end()) {
      return (static_cast<const ValueIteratorImpl *>(this) == &other);
   } else {
      return other.is_end();
   }
}

Value
BSONCType::to_value() const
{
   return Value(*this);
}

const char *
BSONCType::key() const
{
   bson_t bson;
   bson_iter_t iter;
   init_iter(&bson, &iter);

   return bson_iter_key(&iter);
}

}
