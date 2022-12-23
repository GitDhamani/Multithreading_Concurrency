#include <iostream>
#include <thread>
#include <mutex>

/*
Program5: The mutex lock in the previous program is blocking, meaning that threads that are not able 
to acquire the lock fast enough must hold in a waiting pattern until it becomes available. However there are times
you want the thread to check if it can acquire the lock and if not, it can be free to attend to other tasks before 
trying again later. This program shows how to achieve this using the try_lock().
*/

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
