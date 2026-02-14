#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

//
void calsum(int &sum, int valuetoadd)
{
    sum+=valuetoadd;
}

int main()
{
    struct timeval startTime, endTime;
    vector<int> vt={10000,20000,300000,400000,500000};
    int single_thread_sum=0;

    gettimeofday(&startTime, NULL);// start timin
    for (size_t i = 0; i < vt.size(); i++)
    {
        single_thread_sum+=vt[i];
    }
    gettimeofday(&endTime, NULL);//end timing
    double elapsed = (endTime.tv_sec - startTime.tv_sec) * 1000000.0;
    elapsed += (endTime.tv_usec - startTime.tv_usec);  //convert to microseconds
    std::cout << "Elapsed time: " << elapsed << " µs" << std::endl;

    gettimeofday(&startTime, NULL);// start timin
    thread t1(calsum, std::ref(single_thread_sum), vt[0]);
    thread t2(calsum, std::ref(single_thread_sum), vt[1]);
    thread t3(calsum, std::ref(single_thread_sum), vt[2]);
    thread t4(calsum, std::ref(single_thread_sum), vt[3]);
    thread t5(calsum, std::ref(single_thread_sum), vt[4]);
    gettimeofday(&endTime, NULL);//end timing
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    //gettimeofday(&endTime, NULL);//end timing
    elapsed = (endTime.tv_sec - startTime.tv_sec) * 1000000.0;
    elapsed += (endTime.tv_usec - startTime.tv_usec);  //convert to microseconds
    std::cout << "Elapsed time: " << elapsed << " µs" << std::endl;
}
