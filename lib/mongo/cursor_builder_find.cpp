#include "mongo/cursor_builder_find.hpp"
#include "mongo/collection_impl.hpp"
#include "mongo/cursor_impl.hpp"
#include "mongo/utils.hpp"
#include <bson.h>
#include <mongoc.h>

namespace MONGO {

Cursor::Builder::Find::Find(const std::shared_ptr<Collection::Impl> & c, const BSON::Value &query) :
   _collection(c),
   _query(query),
   _fields(),
   _sort()
{
}

std::unique_ptr<Cursor::Impl> Cursor::Builder::Find::to_cursor() const
{
   using namespace BSON;

   Value buf;

   bson_t q;
   bson_t f;

   if (_sort) {
      buf = BSONC(
         "$query", _query,
         "$orderby", _sort
      );
   } else {
      buf = _query;
   }

   Utils::to_bson_t(buf, &q);

   if (_fields) {
      Utils::to_bson_t(_fields, &f);
   }

   mongoc_cursor_t *cursor = mongoc_collection_find(
      _collection->collection.get(),
      (mongoc_query_flags_t) _flags,
      _skip,
      _limit,
      &q,
      (_fields ? &f : NULL),
      NULL
   );

   return std::unique_ptr<Cursor::Impl>(new Cursor::Impl(_collection->client, cursor));
}

auto Cursor::Builder::Find::flags(Flags::Query flags) -> Find &
{
   _flags = flags;

   return *this;
}

auto Cursor::Builder::Find::skip(uint32_t i) -> Find &
{
   _skip = i;

   return *this;
}

auto Cursor::Builder::Find::limit(uint32_t i) -> Find &
{
   _limit = i;

   return *this;
}

auto Cursor::Builder::Find::fields(const BSON::Value &fields) -> Find &
{
   _fields = fields;

   return *this;
}

auto Cursor::Builder::Find::sort(const BSON::Value &sort) -> Find &
{
   _sort = sort;

   return *this;
}

auto Cursor::Builder::Find::read_pref(const ReadPref &rp) -> Find &
{

   return *this;
}


}
