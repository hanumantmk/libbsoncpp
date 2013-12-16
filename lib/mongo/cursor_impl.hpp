#ifndef MONGOCPP_CURSOR_IMPL_H
#define MONGOCPP_CURSOR_IMPL_H

#include "mongo/cursor.hpp"
#include <mongoc.h>
#include <tuple>

namespace MONGO {

class Cursor::Impl {
private:
   std::shared_ptr<Client::Impl> client;
   std::unique_ptr<mongoc_cursor_t, void(*)(mongoc_cursor_t *)> cursor;

public:
   Impl(const std::shared_ptr<Client::Impl> & c, mongoc_cursor_t *cursor) :
      client(c),
      cursor(cursor, &mongoc_cursor_destroy)
   {
   }

   BSON::Value next()
   {
      const bson_t *bson;
      if (mongoc_cursor_next(cursor.get(), &bson)) {
         /* TODO:
          * this is a wee bit dangerous.  Figure out how to track the memory
          * better */

         return BSON::BSONC(std::make_tuple(bson_get_data(bson), bson->len));
      } else {
         bson_error_t error;

         if ( mongoc_cursor_error(cursor.get(), &error) ) {
            using namespace std;

            cout << "Error: " << error.message << endl;
         }

         return BSON::Value();
      }
   }

   bool more() const
   {
      return mongoc_cursor_more(cursor.get());
   }
};

}

#endif
