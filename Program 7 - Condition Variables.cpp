#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

/*
Program7: Here I show how to launch multiple threads at once, but synchronise them using conditional variables. 
This allows a thread to sleep if certain conditions are not met in which case, it will also release any mutex locks it 
has previously acquired. When the conditions are more favourable and perhaps other threads have finished, the thread can 
be re-awakened and asked to re-acquire the lock and see if the conditions are now more suitable for it to continue. 
I use this paradigm in order to ensure that the first thread is always executed before the second thread.
*/

std::mutex m1;
std::condition_variable cv;
bool correctStart{};

void start1()
{
	m1.lock();
	std::cout<<"Start1 Executed."<<std::endl;
	m1.unlock();
	correctStart = true;
	cv.notify_one();
}

void start2()
{
	std::unique_lock<std::mutex> mtx(m1);
	cv.wait(mtx, [](){ return correctStart; });
	std::cout<<"Start2 Executed."<<std::endl;
	m1.unlock();
}

int main()
{
	std::thread worker2(start2);
	std::thread worker1(start1);
	worker2.join();
	worker1.join();
	return 0;
}
