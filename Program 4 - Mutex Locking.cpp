#include <iostream>
#include <thread>
#include <mutex>

/*
Program 4: Here I tackle the issue of Race Hazards when two or more threads are attempting to modify a critical section of code
at the same time. Mutex locking ensures access is provided thread-sequentially, one at a time. This means the entirety of the 
two tasks are done, but not at the same time.
*/

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
