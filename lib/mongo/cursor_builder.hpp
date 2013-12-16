#ifndef MONGOCPP_CURSOR_BUILDER_H
#define MONGOCPP_CURSOR_BUILDER_H

#include "mongo/cursor.hpp"
#include "mongo/flags.hpp"
#include "mongo/client.hpp"

#include <bson.hpp>

namespace MONGO {

class Cursor::Builder {
   friend class Cursor;

public:
   class Find;

protected:
   virtual std::unique_ptr<Cursor::Impl> to_cursor() const = 0;

public:
   virtual ~Builder() {}
};

}

#endif
