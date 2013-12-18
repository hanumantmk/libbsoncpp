#include "mongo/collection_impl.hpp"

namespace MONGO {

Collection::Collection(const std::shared_ptr<ClientImpl> & c, const char * db, const char * name) :
   impl(new CollectionImpl(c, db, name))
{
}

}
