#include <iostream>
#include <thread>
#include <mutex>

int count = 0;
std::mutex m;

void incCount()
{
	for (int i = 0; i<1'000'000; i++)
	{
		if (m.try_lock())
		{
		count++;
		m.unlock();
		}
	}
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