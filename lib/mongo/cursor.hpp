#ifndef MONGOCPP_CURSOR_H
#define MONGOCPP_CURSOR_H

#include "mongo/client.hpp"
#include <bson.hpp>

namespace MONGO {

class CursorImpl;
class CursorBuilder;

class Cursor {
   std::shared_ptr<CursorImpl> impl;

public:
   Cursor(std::unique_ptr<CursorImpl> && impl);
   Cursor(const CursorBuilder &b);

   BSON::Value next();
   bool more() const;
};

}

#endif
