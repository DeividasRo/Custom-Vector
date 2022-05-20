#include <iostream>
#include <vector>
#include <chrono>
#include "myvector.h"

using namespace std::chrono;

void test1(int sz)
{
    duration<double> diff; // 100000, 1000000, 10000000, 100000000
    std::cout << "SIZE " << sz << std::endl;
    auto start = high_resolution_clock::now();
    std::vector<int> std_vec;
    for (int i = 1; i <= sz; ++i)
        std_vec.push_back(i);
    auto end = high_resolution_clock::now();
    diff = end - start;

    std::cout << "STL Vector: " << diff.count() << " s" << std::endl;

    start = high_resolution_clock::now();
    Vector<int> my_vec;
    for (int i = 1; i <= sz; ++i)
        my_vec.push_back(i);

    end = high_resolution_clock::now();
    diff = end - start;

    std::cout << "My Vector: " << diff.count() << " s" << std::endl;
}
template <typename T>
int test2(int sz, T vec)
{
    int count = 0;
    for (int i = 1; i <= sz; ++i)
    {
        vec.push_back(i);
        if (vec.capacity() == vec.size())
            count++;
    }
    return count;
}

int main()
{
    test1(10000);
    test1(100000);
    test1(1000000);
    test1(10000000);
    test1(100000000);

    std::vector<int> std_vec;
    Vector<int> my_vec;

    int std_vec_count = test2(100000000, std_vec);
    int my_vec_count = test2(100000000, my_vec);
    std::cout << std_vec_count << std::endl;
    std::cout << my_vec_count << std::endl;
    return 0;
}