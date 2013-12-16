#ifndef MONGOCPP_CLIENT_IMPL_H
#define MONGOCPP_CLIENT_IMPL_H

#include "mongo/client.hpp"
#include <mongoc.h>
#include <bson.hpp>

namespace MONGO {

class Client::Impl {
   uint32_t batch_size = 0;
   std::unique_ptr<mongoc_client_t, void(*)(mongoc_client_t *)> client;

public:
   Impl(const char * uri_string) :
      client(mongoc_client_new(uri_string), &mongoc_client_destroy)
   {
   }

   mongoc_client_t * get() const
   {
      return client.get();
   }

   uint32_t get_batch_size() const
   {
      return batch_size;
   }
};

}

#endif
