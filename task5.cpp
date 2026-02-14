#include <iostream>
#include <thread>
#include <bits/stdc++.h>

using namespace std;

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

// Have a log wrapper class created and use that class only to log the values

class Logger
{

private:
    std::mutex log_mutex;
    std::ofstream log_file;

public:
    Logger()
    {
        log_file.open("log.txt", std::ios::out | std::ios::app);
        if (!log_file.is_open())
        {
            throw std::runtime_error("Could not open log file");
        }
 //   Note we can do lazy initalization of the log file, using std::call_once(_flag, init_log_file) and then in the init_log_file function we can open the log file. This will ensure that the log file is only opened once and will be thread safe.
    }
    void log(const std::string& message)
    {
        std::lock_guard<std::mutex> lock(log_mutex);

        // if we are using unique_lock , we can unique_lock(mutex, std:: defer_lock) and then lock and unlock the mutex manually.
        // This will give us more control over the locking and unlocking of the mutex.

        // eg - std::unique_lock<std::mutex> lock(log_mutex, std::defer_lock);
        // lock.lock();
        log_file << message << std::endl;
        // lock.unlock();
    }
};

void test_print(Logger& logger, string value)
{
for (int i = 0; i < 5; ++i)
    logger.log("Thread " + value + " is executing with thread id " + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())));
}

int main()
{
    int n = 0;
	int pass_by_ref=30;
    Logger logger;
    thread t3(test_print, std::ref(logger), "test");
    for (size_t i = 0; i < 5; i++)
    {
        logger.log("Main thread is executing with thread id " + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())));
    }
    t3.join();

}
