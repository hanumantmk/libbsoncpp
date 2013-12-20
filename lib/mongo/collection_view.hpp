#ifndef MONGOCPP_CURSOR_BUILDER_FIND_H
#define MONGOCPP_CURSOR_BUILDER_FIND_H

#include <bson.hpp>

#include "mongo/flags.hpp"
#include "mongo/cursor.hpp"

namespace MONGO {

class CollectionImpl;

class CollectionView {
friend class Collection;

private:
   std::shared_ptr<CollectionImpl> _collection;
   BSON::Value _query;
   BSON::Value _sort;
   BSON::Value _fields;
   uint32_t _skip = 0;
   uint32_t _limit = 0;

   CollectionView(const std::shared_ptr<CollectionImpl> & c, const BSON::Value &query);

public:
   template <class ...T>
   CollectionView & sort(const T& ...t)
   {
      _sort = BSON::BSONC(t...);

      return *this;
   }

   CollectionView & skip(uint32_t i);
   CollectionView & limit(uint32_t i);

   template <class ...T>
   CollectionView & fields(const T& ...t)
   {
      _fields = BSON::BSONC(t...);

      return *this;
   }

   Cursor get(Flags::Query f = Flags::Query::NONE) const;

   uint64_t count(Flags::Query f = Flags::Query::NONE) const;
};

}

#endif
