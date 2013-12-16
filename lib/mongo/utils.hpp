#ifndef MONGOCPP_UTILS_H
#define MONGOCPP_UTILS_H

extern "C" {
#include <mongoc.h>
}

#include <bson.hpp>

namespace MONGO {

namespace Utils {

void to_bson_t(const BSON::Value & v, bson_t * out);

}

}

#endif
