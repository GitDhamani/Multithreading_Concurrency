#include <iostream>
#include <thread>
#include <mutex>

int count = 0;
std::mutex m;

void incCount()
{
	m.lock();
	count++;
	std::cout<<"Count is incremented to: "<<count<<std::endl;
	m.unlock();
}

int main()
{
	std::thread worker1(incCount);
	std::thread worker2(incCount);
	worker1.join();
	worker2.join();
	std::cout<<"Count is now: "<<count<<std::endl;

	return 0;
}
