#ifndef BSONCPP_H
#define BSONCPP_H

#include <memory>
#include "ibson.hpp"

extern "C" {
#include <bson.h>
}

class BSON : public IBSON {
private:
   bson_t bson;

public:
   BSON();
   ~BSON();
   BSON (const BSON &other);
   BSON & operator= (const BSON &other);

   virtual void
   toBson (void  **buf,
           size_t *len);

   virtual void
   append (std::string key,
           int32_t     i);

   virtual void
   append (std::string key,
           std::string s);
};

#endif
