#ifndef BSONCPP_INTERFACE_H
#define BSONCPP_INTERFACE_H

#include <unistd.h>
#include <cstdint>
#include <string>

class IBSON {
public:
   virtual ~IBSON()
   {
   };

   virtual void
   toBson (void  **buf,
           size_t *len) = 0;

   virtual void
   append (std::string key,
           int32_t     i) = 0;

   virtual void
   append (std::string key,
           std::string s) = 0;
};

#endif
