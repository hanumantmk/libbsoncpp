#include "mongo/utils.hpp"

namespace MONGO {
namespace Utils {

void to_bson_t(const BSON::Value & v, bson_t * out)
{
   const uint8_t * buf;
   size_t len;

   std::tie(buf, len) = v.to_bson();

   bson_init_static(out, buf, len);
}

}
}
