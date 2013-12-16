#ifndef MONGOCPP_DATABASE_H
#define MONGOCPP_DATABASE_H

#include "mongo/client.hpp"

namespace MONGO {

class Database {
private:
   friend class Client;

public:
   class Impl;

private:
   std::shared_ptr<Database::Impl> impl;
   Database(const Client & c, const char * db);

public:
   Collection get_collection(const char * name);
};

}

#endif
