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
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo
{
public:
    void bar()
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "Thread 3 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

class Functor
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "Thread 4 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

int main()
{
    int n = 0;
	int pass_by_ref=0;
    foo f;
    Functor fnctor;
    std::thread t1; // t1 is not a thread
    std::thread t2(function_pass_by_value, n + 1); // pass by value
    std::thread t3(function_pass_by_ref, std::ref(pass_by_ref)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running function_pass_by_ref(). t3 is no longer a thread
    std::thread t5(&foo::bar, &f); // t5 runs foo::bar() on object f
    std::thread t6(fnctor); // t6 runs Functor::operator() on a copy of object fnctor
    t2.join();
    t4.join();
    t5.join();

	//t6.join();
	t6.detach(); // Detaching t6, it will continue to run independently

	if(t6.joinable()) {
		t6.join(); // This will not execute as t6 is detached
	} else {
		std::cout << "t6 is not joinable, it has been detached.\n";
	}

    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of pass_by_ref is " << pass_by_ref << '\n';
    std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
    std::cout << "Final value of fnctor.n (Functor::n) is " << fnctor.n << '\n';
}
