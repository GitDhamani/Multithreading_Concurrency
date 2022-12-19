#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <chrono>

std::mutex m1;
std::condition_variable cv;
std::vector<int> vec;

void producer(int val)
{
	while(val)
	{
	std::unique_lock<std::mutex> L1(m1);
	cv.wait(L1, [](){ return vec.size() < 10;});
	vec.push_back(val);
	std::cout<<val<<" produced."<<std::endl;
	val--;
	m1.unlock();
	cv.notify_one();
	}
}

void consumer()
{
	while(true)
	{
	std::unique_lock<std::mutex> L2(m1);
	cv.wait(L2, [](){ return vec.size() > 0;});
	while(vec.size())
	{
	std::cout<<"Consumed "<<vec.back()<<std::endl;
	vec.pop_back();
	}
	m1.unlock();
	cv.notify_one();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	std::thread T1(producer, 100);
	std::thread T2(consumer);
	T1.join();
	T2.join();
	return 0;
}
