#include "mongo/cursor_builder_find.hpp"
#include "mongo/collection_impl.hpp"
#include "mongo/cursor_impl.hpp"
#include "mongo/utils.hpp"
#include <bson.h>
#include <mongoc.h>

namespace MONGO {

CursorBuilderFind::CursorBuilderFind(const std::shared_ptr<CollectionImpl> & c, const BSON::Value &query) :
   _collection(c),
   _query(query),
   _fields()
{
}

std::unique_ptr<CursorImpl> CursorBuilderFind::to_cursor() const
{
   bson_t q;
   bson_t f;

   Utils::to_bson_t(_query, &q);

   if (_fields) {
      Utils::to_bson_t(_fields, &f);
   }

   mongoc_cursor_t *cursor = mongoc_collection_find(
      _collection->collection.get(),
      (mongoc_query_flags_t) _flags,
      _skip,
      _limit,
      &q,
      (_fields ? &f : nullptr),
      nullptr
   );

   return std::unique_ptr<CursorImpl>(new CursorImpl(_collection->client, cursor));
}

auto CursorBuilderFind::flags(Flags::Query flags) -> CursorBuilderFind &
{
   _flags = flags;

   return *this;
}

auto CursorBuilderFind::skip(uint32_t i) -> CursorBuilderFind &
{
   _skip = i;

   return *this;
}

auto CursorBuilderFind::limit(uint32_t i) -> CursorBuilderFind &
{
   _limit = i;

   return *this;
}

auto CursorBuilderFind::read_pref(const ReadPref &rp) -> CursorBuilderFind &
{

   return *this;
}

}
