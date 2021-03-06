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

   col.drop();

   col.insert({ BSONC("hello", "goodbye"), BSONC("hello", 12) });

   CollectionView v = col.find().fields("hello", 1, "_id", 0).sort("hello", -1);

   cout << "Count is: " << v.count() << endl;

   Cursor cursor = v.limit(2).get();

   while ( Value v = cursor.next() ) {
      cout << v["hello"] << endl;
   }
}
