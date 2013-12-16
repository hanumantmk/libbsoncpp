#include "mongo.hpp"

#include <iostream>

using namespace std;
using namespace BSON;
using namespace MONGO;

int
main (int    argc,
      char **argv)
{
   Client c("mongodb://127.0.0.1/");

   Collection col = c.get_collection( "test", "test");

   Cursor cursor = col.find(BSONC("hello", "world")).fields(BSONC("hello", 1, "_id", 0));

   while (true) {
      Value v = cursor.next();
      if (! v) {
         break;
      }

      cout << v << endl;
   }
}
