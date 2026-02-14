#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

queue<int> q;
mutex mtx;

void func_sender()
{
    int count=0;
    while(count < 10)
    {
        unique_lock<mutex> locker(mtx);
        q.push(count);
        locker.unlock();
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
        if(!q.empty())
        {
            int value = q.front();
            q.pop();
            locker.unlock();
            count++;
            cout << "Received: " << value << endl;
        }
        else
        {
            cout << "Queue is empty, waiting for sender..." << endl;
            locker.unlock();
        }

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


//Here receiver keeps waiting in busy loop until sender sends something.
// This is not efficient as receiver is consuming CPU cycles while waiting for sender to send something.
// We can use condition variable to avoid this busy waiting and make receiver wait until sender sends something.