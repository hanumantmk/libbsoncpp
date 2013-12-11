#ifndef BSONCPP_STACK_H
#define BSONCPP_STACK_H

#include <type_traits>
#include <memory>
#include <list>

namespace BSON {
using namespace std;

template<typename T, size_t size>
class Stack
{
   typename aligned_storage<sizeof(T), alignof(T)>::type base[size];
   typedef list<T *> list_t;

   list_t storage;
   typename list_t::iterator iter;
   int i = 0;
   int bucket_size = size;
   bool is_empty = true;

   T * _get_ptr()
   {
      return *(iter) + i;
   }

   void _inc()
   {
      if (i == bucket_size - 1) {
         typename list_t::iterator tmp_iter = iter;

         i = 0;
         bucket_size <<= 1;

         if (++tmp_iter == storage.end()) {
            auto tmp = get_temporary_buffer<T> (bucket_size);
            storage.emplace_back(tmp.first);
         }

         ++iter;
      } else {
         ++i;
      }
   }

   void _dec()
   {
      _get_ptr()->~T();

      if (i == 0) {
         if (iter == storage.begin()) {
            is_empty = true;
         } else {
            --iter;
            bucket_size >>= 1;
            i = bucket_size -1;
         }
      } else {
         --i;
      }
   }

public:
   Stack() :
      storage({static_cast<T *>(static_cast<void *>(base))}),
      iter(storage.begin())
   {
   }

   ~Stack() {
      while (! empty()) {
         pop();
      }

      while (storage.size() > 1) {
         return_temporary_buffer(storage.back());
         storage.pop_back();
      }
   }

   bool empty() const
   {
      return is_empty;
   }

   T & top()
   {
      return *(_get_ptr());
   }

   template <typename ...Args>
   void emplace(Args&&... args)
   {
      if (is_empty) {
         is_empty = false;
      } else {
         _inc();
      }

      new (_get_ptr()) T(forward<Args>(args)...);
   }

   void pop()
   {
      _dec();
   }

};

}

#endif
