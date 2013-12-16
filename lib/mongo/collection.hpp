#ifndef MONGOCPP_COLLECTION_H
#define MONGOCPP_COLLECTION_H

#include "mongo/client.hpp"
#include "mongo/cursor_builder.hpp"

#include <bson.hpp>

namespace MONGO {

class Collection {
private:
   friend class Client;

public:
   class Impl;

private:
   std::shared_ptr<Impl> impl;
   Collection(const std::shared_ptr<Client::Impl> & c, const char * db, const char * name);

public:
   Cursor::Builder::Find find(const BSON::Value & query) const;

};

}

#endif
