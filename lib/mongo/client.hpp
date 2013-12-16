#ifndef MONGOCPP_CLIENT_H
#define MONGOCPP_CLIENT_H

#include <memory>

namespace MONGO {

class Database;
class Collection;
class WriteConcern;
class ReadPref;

class Client {
public:
   class Impl;

private:
   std::shared_ptr<Impl> impl;

public:
   Client(const Client &other);
   Client(const char * uri_string);

   Database get_database(const char * name) const;
   Collection get_collection(const char * db, const char * name) const;
};

}

#endif
