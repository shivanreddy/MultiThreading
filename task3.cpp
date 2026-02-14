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
        std::lock_guard<std::mutex> lock(mutex_cout);
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
        std::lock_guard<std::mutex> lock(mutex_cout);
        std::cout << "Main thread executing with thread id " << std::this_thread::get_id() << " and value of pass_by_ref " << pass_by_ref << "\n";
        pass_by_ref--;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::thread t4(std::move(t3)); // t4 is now running function_pass_by_ref(). t3 is no longer a thread
    t4.join();


    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of pass_by_ref is " << pass_by_ref << '\n';
}