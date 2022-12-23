#include <iostream>
#include <thread>
#include <mutex>

/*
Program 8: Here I mischieviously try and create a deadlock, where the two threads get stuck waiting for each other in an 
endless tug of war. The two threads launch FuncA and FuncB respectively. However FuncA locks mutex M1 and M2 in that order, 
and FuncB locks mutex M2 and M1 and in that order. So what tends to happen is either function will obtain the first lock without
any issue but will then halt whilst trying to acquire the second lock. However acquiring that lock will not be possible as the 
other thread has already obtained it, hence the deadlock.
*/

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
