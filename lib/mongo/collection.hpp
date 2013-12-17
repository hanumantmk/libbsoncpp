#ifndef MONGOCPP_COLLECTION_H
#define MONGOCPP_COLLECTION_H

#include <bson.hpp>

#include "cursor_builder_find.hpp"

namespace MONGO {

class CollectionImpl;
class ClientImpl;
class CursorBuilderFind;

class Collection {
friend class Client;

private:
   std::shared_ptr<CollectionImpl> impl;
   Collection(const std::shared_ptr<ClientImpl> & c, const char * db, const char * name);

public:
   template <class ...T>
   CursorBuilderFind find(const T& ...t) const
   {
      auto i = sizeof...(T);

      if (i) {
         return CursorBuilderFind(impl, BSON::BSONC("$query", '{', t..., '}'));
      } else {
         return CursorBuilderFind(impl, BSON::BSONC("$query", '{', '}'));
      }
   }
};

};

#endif
