#include <iostream>
#include <thread>
#include <mutex>

/*
Program 9: Here I take the deadlock from the last Program and show how to avoid it using std::lock(). 
This is an interesting multi-mutex locking mechanism and will continuously try to lock and unlock all the mutex 
objects you pass in to it. If successful it will lock all the mutex object parameters, otherwise it will unlock 
any acquired mutex locks and wait on any specific one it has had trouble with. This means both threads are now 
trying to lock the same two mutex objects at the same time, but through the use of std::lock(), there are no deadlocks.
*/

std::mutex m1, m2;

void funcA()
{
	while(true)
	{
	std::lock(m1, m2);
	std::cout<<"Function A obtained the Lock."<<std::endl;
	m1.unlock();
	m2.unlock();
	}
}

void funcB()
{
	while(true)
	{
	std::lock(m1, m2);
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
