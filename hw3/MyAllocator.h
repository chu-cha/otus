#pragma once 

#include <memory>

template <typename  T, size_t N = 10>
class MyAllocator
{
public:
    using value_type = T;

    MyAllocator() noexcept
        : used(0), 
#ifdef _MSC_VER
        PoolSize(N + 1),
#else 
        PoolSize(N), // different behavior of msvc: allocating tail node for some containers (like map) dynamically
#endif
         
        pool(nullptr)
    {
        //std::cout << "Ctor: " << typeid(T).name() << "\n";
    }

    ~MyAllocator()
    {
        //std::cout << "Allocator dtor " << std::endl;
    }

    T* allocate(std::size_t n)
    {
        if (!pool) {
            pool.reset(static_cast<T*>(::operator new(PoolSize * sizeof(T))));
        }

        if (used + n > PoolSize)
            throw std::bad_alloc(); //todo

        auto mem_pool = pool.get();
        auto ret = &mem_pool[used];
#ifdef _MSC_VER
        used += n;
#endif   
        return ret;
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
       // std::cout << "construct " << typeid(*p).name() << "\n";
        new(p) U(std::forward<Args>(args)...);
#ifndef _MSC_VER
        used++;
#endif
    }

    void deallocate(T* p, std::size_t n)
    {
        //do nothing, all work will be done when allocator destructor is called (shared_ptr as RAII)
        //std::cout << "deallocate " << typeid(*p).name() << "\n";
    }

    template <typename U>
    void destroy(U* p)
    {
        //std::cout << "destroy " << typeid(*p).name() << "\n";
        p->~U();
    }

    template <class U>
    struct rebind
    {
        using other = MyAllocator<U, N>;
    };

private:

    std::size_t used;
    std::shared_ptr<T> pool;
    std::size_t PoolSize;

};

template <class T, class U>
constexpr bool operator==(const MyAllocator<T>& a1, const MyAllocator<U>& a2) noexcept
{
    return a1.pool == a2.pool;
}

template <class T, class U>
constexpr bool operator!=(const MyAllocator<T>& a1, const MyAllocator<U>& a2) noexcept
{
    return a1.pool != a2.pool;
}