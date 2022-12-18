#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

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