#ifndef MONGOCPP_CURSOR_H
#define MONGOCPP_CURSOR_H

#include "mongo/client.hpp"
#include <bson.hpp>

namespace MONGO {

class CursorImpl;
class CursorBuilder;
class CollectionView;

class Cursor {
   std::unique_ptr<CursorImpl> impl;

public:
   Cursor(std::unique_ptr<CursorImpl> && impl);
   Cursor(Cursor && c);
   ~Cursor();

   BSON::Value next();
   bool more() const;
};

}

#endif
