#ifndef BSONCPP_BSONC_UTF8_H
#define BSONCPP_BSONC_UTF8_H

#include "bson_bsonc_type.hpp"

namespace BSON {

class BSONC::Type::UTF8 : public BSONC::Type {
private:
   const char *val;

public:
   UTF8 (const std::shared_ptr<bson_t> &b, const char *v);

   void print (std::ostream & stream) const;
};

}

#endif
