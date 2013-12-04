#ifndef BSONCPP_BSONC_UTF8_H
#define BSONCPP_BSONC_UTF8_H

#include "bson_bsonc.hpp"
#include "bson_value_impl.hpp"

namespace BSON {

class BSONC::UTF8 : public Value::Impl {
private:
   std::shared_ptr<bson_t> bson;
   const char *val;

public:
   UTF8 (const std::shared_ptr<bson_t> &i, const char *v);

   void print (std::ostream & stream) const;
};

}

#endif
