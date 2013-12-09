#include "bson.hpp"

#include <iostream>

using namespace std;
using namespace BSON;

int
main (int    argc,
      char **argv)
{
   Value v;

   {
      BSONC bson(
         "foo", "bar",
         "bson", BSONC(
            "a", 1,
            "b", 2,
            "c", 3,
            "doc", BSONC::Doc(
               "d", NULL,
               "array", BSONC::Array( 10, 11, 12),
               "array", BSONC::TArray(), 10, 11, 12, BSONC::TEnd(),
               "e", 2,
               "f", 3
            )
         ),
         "baz", "bop",
         "lol", 10
      );

      cout << bson << endl;

      cout << "not real: " << bson["not real"] << endl << "foo: " << bson["foo"] <<
        endl;

      v = bson["bson"]["doc"]["array"];
   }

   cout << v << endl;

   Value z = std::move(v);

   cout << z[1] << endl;
}
