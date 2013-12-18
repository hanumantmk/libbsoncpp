#ifndef MONGOCPP_COLLECTION_H
#define MONGOCPP_COLLECTION_H

#include <bson.hpp>

#include "collection_view.hpp"

namespace MONGO {

class CollectionImpl;
class ClientImpl;
class CollectionView;

class Collection {
friend class Client;

private:
   std::shared_ptr<CollectionImpl> impl;
   Collection(const std::shared_ptr<ClientImpl> & c, const char * db, const char * name);

public:
   template <class ...T>
   CollectionView find(const T& ...t) const
   {
      if (sizeof...(T)) {
         return CollectionView(impl, BSON::BSONC("$query", '{', t..., '}'));
      } else {
         return CollectionView(impl, BSON::BSONC("$query", '{', '}'));
      }
   }
};

};

#endif
