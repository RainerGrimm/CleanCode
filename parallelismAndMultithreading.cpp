// Pablo Camacho

#include <thread>     // For multithreading
#include <algorithm>  // for std::for_each -> Requires C++17, at least
#include <execution>  // for parallel STL algorithm: std::execution::par -> Requires C++17, at least
#include <iostream>

void doubleRangeParallel(std::vector<int> const& input, std::vector<int>& output, size_t start, size_t end)
{
    // Use parallel for_each within each thread for the given range
    size_t index = start;
    std::for_each(std::execution::par, input.begin() + start, input.begin() + end,
        [&output, &index](int n) mutable { output[index++] = n * 2; });
}

int main()
{
    // Since we will not sort the result, pre-ordered container is not required:
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 10, 9, 8};
    std::vector<int> result(data.size());

    // Split work for two threads:
    size_t mid = (data.size() + 1) / 2; // First thread: 0 to mid, second: mid to end

    // Launch two threads, each using parallel for_each
    // Note that no mutex is required since each thread is working on a different vector range:
    // First thread: 0 to mid, second: mid to end
    std::thread t1(doubleRangeParallel, std::ref(data), std::ref(result), 0, mid);
    std::thread t2(doubleRangeParallel, std::ref(data), std::ref(result), mid, data.size());

    // Join and wait for threads to finish
    t1.join();
    t2.join();

    // Print results
    for (int x : result)
    {
        std::cout << x << " "; // Output: 2 4 6 8 10 12 14 20 18 16 
    }

    return 0;
}