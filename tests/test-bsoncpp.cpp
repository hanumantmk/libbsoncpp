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
         "baz", "bop",
         "lol", 10,
         "doc", BSONC(
            "a", 1,
            "b", 2,
            "c", 3
         ),
         "array", BSONC::Array(
            10, 11, 12
         )
      );

      cout << bson << endl;

      cout << "not real: " << bson["not real"] << endl << "foo: " << bson["foo"] <<
        endl;

      v = bson["array"];
   }

   cout << v << endl;

   Value z = std::move(v);

   cout << z << endl;
}
