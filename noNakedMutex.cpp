// Pablo Camacho

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx; // Mutex to protect shared counter: Requires higher scope than the incrementCounter() function.
int counter = 0; // Shared counter

void incrementCounter(int iterations)
{
    // static std::mutex mtx; <-- Would work, but not advisable use of "static" in modern C++

    for (int i = 0; i < iterations; ++i)
    {
        // ERROR! WILL NOT COMPILE: NO NAMED LOCK_GUARD! (NAKED MUTEX)
        // std::lock_guard<std::mutex> (mtx);

        // static std::mutex mtx; <-- Would work, but not advisable use of "static" in modern C++
        
        // CORRECT USE OF LOCK_GUARD:
        std::lock_guard<std::mutex> lock(mtx); // RAII lock, auto-unlocks at end of scope
        ++counter; // Safe increment
    }
}

int main()
{
    int const numThreads = 4;
    int const iterationsPerThread = 1'000;
    std::vector<std::thread> threads;

    // Launch threads
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(incrementCounter, iterationsPerThread);
    }

    // join and wait for threads to finish
    for (auto& t : threads)
    {
        t.join();
    }

    // Print result
    std::cout << "Final counter value: " << counter << "\n"; // Expected: 4000

    return 0;
}