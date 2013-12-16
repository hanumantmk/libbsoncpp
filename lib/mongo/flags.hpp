#ifndef MONGOCPP_FLAGS_H
#define MONGOCPP_FLAGS_H

namespace MONGO {
namespace Flags {

enum Query {
   NONE              = 0,
   TAILABLE_CURSOR   = 1 << 1,
   SLAVE_OK          = 1 << 2,
   OPLOG_REPLAY      = 1 << 3,
   NO_CURSOR_TIMEOUT = 1 << 4,
   AWAIT_DATA        = 1 << 5,
   EXHAUST           = 1 << 6,
   PARTIAL           = 1 << 7,
};

}
}

#endif
