#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void funcA()
{
	while(true)
	{
	m1.lock();
	m2.lock();
	std::cout<<"Function A obtained the Lock."<<std::endl;
	m1.unlock();
	m2.unlock();
	}
}

void funcB()
{
	while(true)
	{
	m2.lock();
	m1.lock();
	std::cout<<"Function B obtained the Lock."<<std::endl;
	m1.unlock();
	m2.unlock();
	}
}

int main()
{
	std::thread worker1(funcA);
	std::thread worker2(funcB);
	worker1.join();
	worker2.join();
	return 0;
}
