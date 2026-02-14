#include <iostream>
#include <thread>
#include <bits/stdc++.h>

using namespace std;

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

void function_pass_by_value(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 1 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void function_pass_by_ref(int& n)
{
    while(n>=0)
    {
        std::cout << "Thread 2 executing with thread id " << std::this_thread::get_id() << " and value of n " << n << "\n";
        n--;
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
        std::cout << "Main thread executing with thread id " << std::this_thread::get_id() << " and value of pass_by_ref " << pass_by_ref << "\n";
        pass_by_ref--;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::thread t4(std::move(t3)); // t4 is now running function_pass_by_ref(). t3 is no longer a thread
    t4.join();

    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of pass_by_ref is " << pass_by_ref << '\n';
}

//Task
// Pass by reference and have 2 thread update the variable


// Output
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 30
// Thread 2 executing with thread id 131746930509568 and value of n 29
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 28
// Thread 2 executing with thread id 131746930509568 and value of n 27
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 26
// Thread 2 executing with thread id 131746930509568 and value of n 25
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 24
// Thread 2 executing with thread id 131746930509568 and value of n 23
// Main thread executing with thread id Thread 2 executing with thread id 131746930509568131746930513728 and value of n  and value of pass_by_ref 2222
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 20
// Thread 2 executing with thread id 131746930509568 and value of n 19
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 18
// Thread 2 executing with thread id 131746930509568 and value of n 17
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 16
// Thread 2 executing with thread id 131746930509568 and value of n 15
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 14
// Thread 2 executing with thread id 131746930509568 and value of n 13
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 12
// Thread 2 executing with thread id 131746930509568 and value of n 11
// Thread 2 executing with thread id 131746930509568 and value of n 10
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 9
// Thread 2 executing with thread id 131746930509568 and value of n 8
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 7
// Thread 2 executing with thread id 131746930509568 and value of n 6
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 5
// Thread 2 executing with thread id 131746930509568 and value of n 4
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 3
// Thread 2 executing with thread id 131746930509568 and value of n 2
// Main thread executing with thread id 131746930513728 and value of pass_by_ref 1
// Thread 2 executing with thread id 131746930509568 and value of n 0
// Final value of n is 0
// Final value of pass_by_ref is -1


// As expected , the cout statements doesnot look neat because of race condition.
// Both the threads are trying to write to the console at the same time.
//To avoid this we can use mutex to lock the cout statements. This will ensure that only one thread can write to the console at a time.


// Continuation in Task3