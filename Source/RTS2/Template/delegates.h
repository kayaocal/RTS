#pragma once

#define MAX_LISTENER_COUNT 10

template <typename P>
class delegate
{
   public:
     delegate():
        ListenerCount(0)
     {
         memset(object_ptrs, 0, sizeof(void*) * MAX_LISTENER_COUNT);
         memset(stub_ptr, 0, sizeof(stub_type) * MAX_LISTENER_COUNT);
     }

    template <class T, void (T::*TMethod)(P)>
    void add(T* object_ptr)
    {
         for(int i = 0; i < MAX_LISTENER_COUNT; i++)
         {
             if(object_ptrs[i] == nullptr)
             {
                 object_ptrs[i] = object_ptr;
                 stub_ptr[i] = &method_stub<T, TMethod>;
                 return;
             }
         }

         // CANT ADD LISTENER TO LIST!
    }

    template <class T, void (T::*TMethod)(P)>
    void remove(T* object_ptr)
    {
         for(int i = 0; i < MAX_LISTENER_COUNT; i++)
         {
             if(object_ptrs[i] != nullptr && object_ptrs[i] == object_ptr)
             {
                 object_ptrs[i] = nullptr;
                 stub_ptr[i] = nullptr;
                 return;
             }
         }

         // CANT FIND LISTENER ON LIST!
    }
    
    template <class T, void (T::*TMethod)(P)>
    static delegate from_method(T* object_ptr)
    {
        delegate d;
        d.object_ptr = object_ptr;
        d.stub_ptr = &method_stub<T, TMethod>; // #1
        return d;
    }

    void operator()(P a1) const
    {
         for(int i = 0; i < MAX_LISTENER_COUNT; i++)
         {
              if(object_ptrs[i] != nullptr)
              {
                  (*stub_ptr[i])(object_ptrs[i], a1);
              }
         }
    }

private:
    typedef void (*stub_type)(void* object_ptr, int);
    void* object_ptrs[MAX_LISTENER_COUNT];
    stub_type stub_ptr[MAX_LISTENER_COUNT];
    int ListenerCount;
    
    template <class T, void (T::*TMethod)(int)>
    static void method_stub(void* object_ptr, P a1)
    {
        T* p = static_cast<T*>(object_ptr);
        return (p->*TMethod)(a1); // #2
    }


};
