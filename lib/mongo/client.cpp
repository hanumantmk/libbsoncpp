#include "mongo/client.hpp"
#include "mongo/client_impl.hpp"
#include "mongo/database.hpp"
#include "mongo/collection.hpp"
#include <mongoc.h>

namespace MONGO {

Client::Client(const Client & other) :
   impl(other.impl)
{
}

Client::Client(const char * uri_string) :
   impl(new Client::Impl(uri_string))
{
}

Database Client::get_database(const char * name) const
{
   return Database(*this, name);
}

Collection Client::get_collection(const char * db, const char * name) const
{
   return Collection(impl, db, name);
}

}
