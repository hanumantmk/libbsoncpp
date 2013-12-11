#include "bson.hpp"

#include <iostream>

using namespace std;
using namespace BSON;

int
main (int    argc,
      char **argv)
{
   int num;

   if (argc == 2) {
      num = atoi(argv[1]);
   } else {
      num = 1;
   }

   for (int i = 0; i < num; i++) {
      BSONC bson;
      bson.append(
         "foo", "bar",
         "bson", BSONC(
            "a", 1,
            "b", 2,
            "c", 3,
            "doc", '{',
               "d", NULL,
               "array", '[', '[', '[', "hi", ']', ']', 10, 11, 12, ']',
               "array", '[', '[', '[', "hi", ']', ']', 10, 11, 12, ']',
               "array", '[', '[', '[', "hi", ']', ']', 10, 11, 12, ']',
               "e", 2,
               "f", 3,
            '}'
         ),
         "baz", "bop",
         "array", '[', 10, 11, 12, ']'
      ).append(
         "array", '[', 10, 11, 12, ']'
      ).append(
         "array", '[', 10, 11, 12
      ).append(
         10, 11, 12
      ).append(
         10, 11, 12
      ).append(
         10, 11, 12
      ).append(
         ']',
         "lol", 10
      );

      cout << bson << endl;

      cout << "not real: " << bson["not real"] << endl << "foo: " << bson["foo"] <<
        endl;

      cout << bson["bson"]["doc"]["array"];
   }
}
