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
      return CollectionView(impl, BSON::BSONC(t...));
   }

   void insert(std::initializer_list<BSON::Value> lst, Flags::Insert i = Flags::Insert::NONE) const;

   void drop() const;
};

};

#endif
