#include "mongo/cursor.hpp"
#include "mongo/cursor_impl.hpp"
#include "mongo/cursor_builder.hpp"

namespace MONGO {

Cursor::Cursor(std::unique_ptr<Impl> && impl) :
   impl(std::move(impl))
{
}

Cursor::Cursor(const Builder &b) :
   impl(std::move(b.to_cursor()))
{
}

BSON::Value Cursor::next()
{
   return impl->next();
}

bool Cursor::more() const
{
   return impl->more();
}

}
