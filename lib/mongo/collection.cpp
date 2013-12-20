#include "mongo/collection_impl.hpp"
#include "mongo/utils.hpp"

#include <vector>

namespace MONGO {

Collection::Collection(const std::shared_ptr<ClientImpl> & c, const char * db, const char * name) :
   impl(new CollectionImpl(c, db, name))
{
}

void Collection::insert(std::initializer_list<BSON::Value> lst, Flags::Insert flags) const
{
   bson_error_t err;
   bool r;
   std::vector<bson_t> b(lst.size());
   std::vector<const bson_t *> bptr(lst.size());

   int i = 0;
   for (auto l : lst) {
      Utils::to_bson_t(l, b.data() + i);
      bptr[i] = b.data() + i;

      i++;
   }

   r = mongoc_collection_insert_bulk(impl->collection.get(), (mongoc_insert_flags_t) flags, bptr.data(), lst.size(), NULL, &err);

   if (! r) {
      throw BSON::Exception(err.message);
   }
}

void Collection::drop() const
{
   bson_error_t err;
   bool r;
   
   r = mongoc_collection_drop(impl->collection.get(), &err);

   if (! r) {
      throw BSON::Exception(err.message);
   }
}

}
