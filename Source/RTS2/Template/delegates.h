#pragma once
#include "RTS2/Prerequisites.h"

#define MAX_LISTENER_COUNT 10

template <typename ...P>
class delegate
{
   public:
    delegate():
       ListenerCount(0)
    {
        memset(object_ptrs, 0, sizeof(void*) * MAX_LISTENER_COUNT);
        memset(stub_ptr, 0, sizeof(stub_type) * MAX_LISTENER_COUNT);
    }

   template <class T, void (T::*TMethod)(P...)>
   void add(T* object_ptr)
   {
        for(int i = 0; i < MAX_LISTENER_COUNT; i++)
        {
            if(object_ptrs[i] == object_ptr)
            {
                LOG_ERR("This Pointer is Already given!! ");
                return;
            }
        }
        for(int i = 0; i < MAX_LISTENER_COUNT; i++)
        {
            if(object_ptrs[i] == nullptr)
            {
                object_ptrs[i] = object_ptr;
                stub_ptr[i] = &method_stub<T, TMethod>;
                ListenerCount++;
                return;
            }
        }

        // CANT ADD LISTENER TO LIST!
   }

   template <class T, void (T::*TMethod)(P...)>
   void remove(T* object_ptr)
   {
        for(int i = 0; i < MAX_LISTENER_COUNT; i++)
        {
            if(object_ptrs[i] != nullptr && object_ptrs[i] == object_ptr)
            {
                object_ptrs[i] = nullptr;
                stub_ptr[i] = nullptr;
                ListenerCount--;
                return;
            }
        }

        // CANT FIND LISTENER ON LIST!
   }

   void operator()(P... a1) const
   {
        if(ListenerCount == 0)
        {
            return;
        }
        
        for(int i = 0; i < MAX_LISTENER_COUNT; i++)
        {
             if(object_ptrs[i] != nullptr)
             {
                 (*stub_ptr[i])(object_ptrs[i], a1...);
             }
        }
   }

   void clear()
   {
       for(int i = 0; i < MAX_LISTENER_COUNT; i++)
       {
            object_ptrs[i] = nullptr;
            stub_ptr[i] = nullptr;
       }
               
       ListenerCount = 0;
   }

    int ListenerCount;
private:
    
    typedef void (*stub_type)(void* object_ptr, P...);
    void* object_ptrs[MAX_LISTENER_COUNT];
    stub_type stub_ptr[MAX_LISTENER_COUNT];
    
    template <class T, void (T::*TMethod)(P...)>
    static void method_stub(void* object_ptr, P... a1)
    {
        T* p = static_cast<T*>(object_ptr);
        return (p->*TMethod)(a1...); // #2
    }


};
