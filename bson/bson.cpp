#include "bson.hpp"
BSON::BSON()
{
   bson_init (&bson);
}

BSON::~BSON()
{
   bson_destroy (&bson);
}

BSON::BSON (const BSON &other)
{

}

BSON & BSON::operator = (const BSON &other)
{

}

void
BSON::toBson (void  **buf,
              size_t *len)
{
   *buf = (void *)bson_get_data(&bson);
   *len = bson.len;
}

void
BSON::append (std::string key,
              int32_t     i)
{
   bson_append_int32(&bson, key.c_str(), key.length(), i);
}

void
BSON::append (std::string key,
              std::string s)
{
   bson_append_utf8(&bson, key.c_str(), key.length(), s.c_str(), s.length());
}
