#ifndef MONGOCPP_CURSOR_IMPL_H
#define MONGOCPP_CURSOR_IMPL_H

#include "mongo/cursor.hpp"
#include "bson/bsonc_type.hpp"
#include <mongoc.h>
#include <tuple>

namespace MONGO {

class CursorImpl {
private:
   std::shared_ptr<ClientImpl> client;
   std::unique_ptr<mongoc_cursor_t, void(*)(mongoc_cursor_t *)> cursor;
   const bson_t * bson;

public:
   CursorImpl(const std::shared_ptr<ClientImpl> & c, mongoc_cursor_t *cursor) :
      client(c),
      cursor(cursor, &mongoc_cursor_destroy)
   {
   }

   BSON::Value next()
   {
      if (mongoc_cursor_next(cursor.get(), &bson)) {
         return BSON::BSONC::Type(bson);
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
