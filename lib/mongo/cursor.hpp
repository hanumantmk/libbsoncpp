#ifndef MONGOCPP_CURSOR_H
#define MONGOCPP_CURSOR_H

#include "mongo/client.hpp"
#include <bson.hpp>

namespace MONGO {

class Cursor {
private:
   class Impl;

public:
   class Builder;

private:
   std::shared_ptr<Impl> impl;

public:
   Cursor(std::unique_ptr<Impl> && impl);
   Cursor(const Builder &b);

   BSON::Value next();
   bool more() const;
};

}

#endif
