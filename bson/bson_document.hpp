#ifndef BSONCPP_DOCUMENT_H
#define BSONCPP_DOCUMENT_H

#include "bson_value_impl.hpp"
#include <unistd.h>
#include <cstdint>
#include <string>
#include <ostream>

namespace BSON {

class Document : public Value::Impl {
public:
   Document(Value::Type t) : Impl(t) {}

   virtual void
   toBson (void  **buf,
           size_t *len) const = 0;

   virtual Value operator [] (const char * s) const = 0;
};

}

#endif
