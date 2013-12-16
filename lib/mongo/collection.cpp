#include "mongo/collection_impl.hpp"
#include "mongo/cursor_builder_find.hpp"

namespace MONGO {

Collection::Collection(const std::shared_ptr<Client::Impl> & c, const char * db, const char * name) :
   impl(new Collection::Impl(c, db, name))
{
}

Cursor::Builder::Find Collection::find(const BSON::Value & query) const
{
   return Cursor::Builder::Find(impl, query);
}

}
