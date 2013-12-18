#include "mongo/cursor.hpp"
#include "mongo/cursor_impl.hpp"
#include "mongo/collection_view.hpp"

namespace MONGO {

Cursor::Cursor(std::unique_ptr<CursorImpl> && impl) :
   impl(std::move(impl))
{
}

Cursor::Cursor(Cursor && c) :
   impl(std::move(c.impl))
{
}

Cursor::~Cursor() = default;

BSON::Value Cursor::next()
{
   return impl->next();
}

bool Cursor::more() const
{
   return impl->more();
}

}
