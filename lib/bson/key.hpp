#ifndef BSONCPP_KEY_H
#define BSONCPP_KEY_H

#include <cstdint>

namespace BSON {

class Key {
   const char * p;
   std::size_t sz;

public:
   template<std::size_t N>
   constexpr Key(const char(&a)[N]) : p(a), sz(N-1) {}

   constexpr Key(const char *a, std::size_t n) : p(a), sz(n) {}

   constexpr std::size_t length() const { return sz; }
   constexpr const char * c_str() const { return p; }
};

}

#endif
