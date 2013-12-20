#include "mongo/collection_view.hpp"
#include "mongo/collection_impl.hpp"
#include "mongo/cursor_impl.hpp"
#include "mongo/utils.hpp"
#include <bson.h>
#include <mongoc.h>

namespace MONGO {

CollectionView::CollectionView(const std::shared_ptr<CollectionImpl> & c, const BSON::Value &query) :
   _collection(c),
   _query(query)
{
}

Cursor CollectionView::get(Flags::Query flags) const
{
   bson_t q;
   bson_t f;

   BSON::BSONC bson("$query", _query);

   if (_sort) {
      bson.append("$orderby", _sort);
   }

   Utils::to_bson_t(bson, &q);

   if (_fields) {
      Utils::to_bson_t(_fields, &f);
   }

   mongoc_cursor_t *cursor = mongoc_collection_find(
      _collection->collection.get(),
      (mongoc_query_flags_t) flags,
      _skip,
      _limit,
      0,
      &q,
      (_fields ? &f : nullptr),
      nullptr
   );

   return Cursor(std::unique_ptr<CursorImpl>(new CursorImpl(_collection->client, cursor)));
}

uint64_t CollectionView::count(Flags::Query flags) const
{
   bson_t q;
   bson_error_t error;

   Utils::to_bson_t(_query, &q);

   int64_t cnt = mongoc_collection_count(
      _collection->collection.get(),
      (mongoc_query_flags_t) flags,
      &q,
      _skip,
      _limit,
      nullptr,
      &error
   );

   if (cnt < 0) {
      throw BSON::Exception(error.message);
   }

   return cnt;
}

auto CollectionView::skip(uint32_t i) -> CollectionView &
{
   _skip = i;

   return *this;
}

auto CollectionView::limit(uint32_t i) -> CollectionView &
{
   _limit = i;

   return *this;
}

}
