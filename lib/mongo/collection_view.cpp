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

   Utils::to_bson_t(_query, &q);

   if (_fields) {
      Utils::to_bson_t(_fields, &f);
   }

   mongoc_cursor_t *cursor = mongoc_collection_find(
      _collection->collection.get(),
      (mongoc_query_flags_t) flags,
      _skip,
      _limit,
      &q,
      (_fields ? &f : nullptr),
      nullptr
   );

   return Cursor(std::unique_ptr<CursorImpl>(new CursorImpl(_collection->client, cursor)));
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
