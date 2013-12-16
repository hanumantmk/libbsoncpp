#include "mongo/database.hpp"
#include "mongo/collection.hpp"

namespace MONGO {

class Database::Impl {
public:
   const char * db;

   Impl(const char * db) : db(db) {}
};

Database::Database(const Client & c, const char * db) :
   impl(new Database::Impl(db))
{
}

Collection Database::get_collection(const char * name)
{
   throw("huh");
}

}
