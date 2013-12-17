#ifndef MONGOCPP_CURSOR_BUILDER_FIND_H
#define MONGOCPP_CURSOR_BUILDER_FIND_H

#include "mongo/cursor_builder.hpp"

#include <bson.hpp>

namespace MONGO {

class CollectionImpl;

class CursorBuilderFind : public CursorBuilder {
friend class Collection;

private:
   std::shared_ptr<CollectionImpl> _collection;
   BSON::Value _query;
   BSON::Value _fields;
   uint32_t _skip = 0;
   uint32_t _limit = 0;
   Flags::Query _flags = Flags::Query::NONE;

   CursorBuilderFind(const std::shared_ptr<CollectionImpl> & c, const BSON::Value &query);

protected:
   std::unique_ptr<CursorImpl> to_cursor() const;

public:
   CursorBuilderFind & flags(Flags::Query flags);

   template <class ...T>
   CursorBuilderFind & sort(const T& ...t)
   {
      _query.to_document().append("$orderby", '{', t..., '}');

      return *this;
   }

   CursorBuilderFind & skip(uint32_t i);
   CursorBuilderFind & limit(uint32_t i);

   template <class ...T>
   CursorBuilderFind & fields(const T& ...t)
   {
      _fields = BSON::BSONC(t...);

      return *this;
   }

   CursorBuilderFind & read_pref(const ReadPref &rp);
};

}

#endif
