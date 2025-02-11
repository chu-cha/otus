#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <numeric>

#include "ForwardList.h"
#include "MyAllocator.h"

template<typename T>
void print(T& v, std::string msg = "") 
{
    //std::cout << "--- " << msg << "---\n";
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<typename T::value_type>(std::cout, " "));
    std::cout << std::endl;
}

template<typename T>
void print_map(const T& m, std::string msg = "") 
{
    //std::cout << "+++ " << msg << "+++\n";
    for (const auto& p : m)
        std::cout << p.first << " " << p.second << '\n';
}

int main()
{
    constexpr int N = 10;

    auto fill_map_with_factorial = [N](auto& m) {
        m[0] = 1;

        for (auto i = 1; i < N; ++i)
            m[i] = m[i - 1] * i;
        };

    // 1. defaul std::map
    std::map<int, int> m;
    fill_map_with_factorial(m);

    // 2. defaul std::map with custom allocator
    std::map<int, int, std::less<int>, MyAllocator<std::pair< const int, int>, N> > my_m;
    fill_map_with_factorial(my_m);
    print_map(my_m, "my map");

    // 3. custom ciontainer with default allocator
    ForwardList<int> fl(10);
    std::iota(fl.begin(), fl.end(), 0);
    print(fl, "My list");

    // 4. custom ciontainer with custom allocator
    ForwardList<int, MyAllocator<int, 10> > fl_w_my_alloc(10);
    std::iota(fl_w_my_alloc.begin(), fl_w_my_alloc.end(), 0);
    print(fl_w_my_alloc, "My list with my alloc");

    return 0;
}

