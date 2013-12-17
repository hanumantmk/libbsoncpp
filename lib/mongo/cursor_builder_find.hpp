#ifndef MONGOCPP_CURSOR_BUILDER_FIND_H
#define MONGOCPP_CURSOR_BUILDER_FIND_H

#include "mongo/collection.hpp"
#include "mongo/cursor_builder.hpp"

namespace MONGO {

class Cursor::Builder::Find : public Cursor::Builder {
   friend class Collection;

private:
   std::shared_ptr<Collection::Impl> _collection;
   BSON::Value _query;
   BSON::Value _fields;
   BSON::Value _sort;
   uint32_t _skip = 0;
   uint32_t _limit = 0;
   Flags::Query _flags = Flags::Query::NONE;

   Find(const std::shared_ptr<Collection::Impl> & c, const BSON::Value &query);

protected:
   std::unique_ptr<Cursor::Impl> to_cursor() const;

public:
   Find & flags(Flags::Query flags);
   Find & sort(const BSON::Value &sort);
   Find & skip(uint32_t i);
   Find & limit(uint32_t i);
   Find & fields(const BSON::Value &fields);
   Find & read_pref(const ReadPref &rp);
};

}

#endif
