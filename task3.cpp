#include <iostream>
#include <thread>
#include <bits/stdc++.h>

using namespace std;

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

mutex  mutex_cout;

void function_pass_by_ref(int& n)
{
    while(n>=0)
    {
        mutex_cout.lock();
        std::cout << "Thread 2 executing with thread id " << std::this_thread::get_id() << " and value of n " << n << "\n";
        n--;
        mutex_cout.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main()
{
    int n = 0;
	int pass_by_ref=30;

    std::thread t3(function_pass_by_ref, std::ref(pass_by_ref)); // pass by reference
    while(pass_by_ref>=0)
    {
        mutex_cout.lock();
        std::cout << "Main thread executing with thread id " << std::this_thread::get_id() << " and value of pass_by_ref " << pass_by_ref << "\n";
        pass_by_ref--;
        mutex_cout.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::thread t4(std::move(t3)); // t4 is now running function_pass_by_ref(). t3 is no longer a thread
    t4.join();


    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of pass_by_ref is " << pass_by_ref << '\n';
}

// Tasl is use mutex to avoid cout race condition


// Output

// Main thread executing with thread id 126046649075520 and value of pass_by_ref 30
// Thread 2 executing with thread id 126046649071360 and value of n 29
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 28
// Thread 2 executing with thread id 126046649071360 and value of n 27
// Thread 2 executing with thread id 126046649071360 and value of n 26
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 25
// Thread 2 executing with thread id 126046649071360 and value of n 24
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 23
// Thread 2 executing with thread id 126046649071360 and value of n 22
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 21
// Thread 2 executing with thread id 126046649071360 and value of n 20
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 19
// Thread 2 executing with thread id 126046649071360 and value of n 18
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 17
// Thread 2 executing with thread id 126046649071360 and value of n 16
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 15
// Thread 2 executing with thread id 126046649071360 and value of n 14
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 13
// Thread 2 executing with thread id 126046649071360 and value of n 12
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 11
// Thread 2 executing with thread id 126046649071360 and value of n 10
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 9
// Thread 2 executing with thread id 126046649071360 and value of n 8
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 7
// Thread 2 executing with thread id 126046649071360 and value of n 6
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 5
// Thread 2 executing with thread id 126046649071360 and value of n 4
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 3
// Thread 2 executing with thread id 126046649071360 and value of n 2
// Main thread executing with thread id 126046649075520 and value of pass_by_ref 1
// Thread 2 executing with thread id 126046649071360 and value of n 0
// Main thread executing with thread id 126046649075520 and value of pass_by_ref -1
// Final value of n is 0
// Final value of pass_by_ref is -2


// there is  a posibility that cout throws errors and mutex lock in not realease at all.

// Continuation task 4
// To avoid this we can use lock_guard which will automatically release the lock when it goes out of scope. This will ensure that the lock is always released even if an exception is thrown.