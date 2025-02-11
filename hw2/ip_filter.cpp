#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>


template<typename T>
std::vector<T> split(std::string str, char delimiter)
{
    std::vector<T> res;
    size_t start = 0;
    size_t pos = 0;

    auto push_to_res = [&res](std::string s) {
        std::stringstream ss;
        ss << s;
        T val;
        ss >> val;
        res.push_back(val); };

    while ((pos = str.find(delimiter, start)) != std::string::npos) {
        push_to_res(str.substr(start, pos));
        start = pos + 1;
    }
    push_to_res(str.substr(start));

    return res;
}


template<typename T>
void print(const std::vector<std::vector<T>>& ip_pool)
{
    for (const auto& ip : ip_pool)
    {
        for (auto i = 0; i < ip.size() - 1; i++)
            std::cout << ip[i] << ".";

        std::cout << ip.back() << '\n';
    }
}


int main()
{
    try
    {
        std::vector<std::vector<int>> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split<std::string>(line, '\t');
            ip_pool.push_back(split<int>(v.at(0), '.'));
        }

        auto ip_sort = [](auto& ip_pool) {
            std::sort(ip_pool.begin(), ip_pool.end(), std::greater<decltype(ip_pool.front())>());
            return ip_pool;
            };

        auto filter = [&ip_pool](int part_value_1, int part_value_2 = -1) {

            std::remove_reference_t<decltype(ip_pool)> res;

            std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(res), [part_value_1, part_value_2](const auto& ip) {

                return ((ip[0] == part_value_1) && ((part_value_2 >= 0) ? (ip[1] == part_value_2) : true)); });
            return res;
            };

        auto filter_any = [&ip_pool](int value) {

            std::remove_reference_t<decltype(ip_pool)> res;

            std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(res), [value](const auto& ip) {

                bool r = false;

                for (const auto& p : ip)
                    if (p == value) {
                        r = true;
                        break;
                    }
                return r;

                ; });

            return res;
            };

        print(ip_sort(ip_pool));
        print(filter(1));
        print(filter(46, 70));
        print(filter_any(46)); 
        


        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
