#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

// using condition variable to avoid busy waiting in receiver thread.
// Receiver will wait until sender sends something and then it will wake up and process the received value.
queue<int> q;
mutex mtx;
condition_variable cv;

void func_sender()
{
    int count=0;
    while(count < 10)
    {
        unique_lock<mutex> locker(mtx);
        q.push(count);
        locker.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
        count++;
    }
}

void func_receiver()
{
    int count=0;
    while(count < 10)
    {
        unique_lock<mutex> locker(mtx);
        cv.wait(locker, []{ return !q.empty(); });
        int value = q.front();
        q.pop();
        locker.unlock();
        count++;
        cout << "Received: " << value << endl;
        cout << "Queue size: " << q.size() << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main()
{
    thread sender(func_sender);
    thread receiver(func_receiver);

    sender.join();
    receiver.join();

    return 0;
}
