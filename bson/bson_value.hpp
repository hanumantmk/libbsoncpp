#ifndef BSONCPP_VALUE_H
#define BSONCPP_VALUE_H

#include <ostream>
#include <memory>

namespace BSON {

class Value {
public:
   class Impl;

private:
   std::unique_ptr<Impl> impl;

public:
   enum Type
   {
      Root,
      Document,
      Array,
      Null,
      UTF8,
   };

   Value ();

   Value (Impl *p) : impl(p) {}

   Type get_type () const;

   void
   print (std::ostream & stream) const;
};

}

std::ostream & operator << (std::ostream & out, const BSON::Value &obj);

#endif
