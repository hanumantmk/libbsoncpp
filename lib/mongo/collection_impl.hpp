#ifndef MONGOCPP_COLLECTION_IMPL_H
#define MONGOCPP_COLLECTION_IMPL_H

#include "mongo/collection.hpp"
#include "mongo/client_impl.hpp"

namespace MONGO {

class CollectionImpl {
public:
   std::shared_ptr<ClientImpl> client;
   std::unique_ptr<mongoc_collection_t, void(*)(mongoc_collection_t *)> collection;

   CollectionImpl(const std::shared_ptr<ClientImpl> & c, const char * db, const char * name) :
      client(c),
      collection(mongoc_client_get_collection(client->get(), db, name), &mongoc_collection_destroy)
   {
   }
};

}

#endif
