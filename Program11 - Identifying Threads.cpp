#include <iostream>
#include <thread>
#include <mutex>
#include <string>

/*
Program 11: Here is where I distinguish which thread has actually acquired the mutex lock on the critical sections 
by pulling its Thread ID. It seems in general the main thread has the ID of 1, and then every new thread created 
goes up sequentially.
*/

std::mutex m1;

void RandomFunc(std::string str)
{
	m1.lock();
	std::cout<<"Acquired by Thread "<<str<<" with ID: "<<std::this_thread::get_id()<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m1.unlock();
}

int main()
{
	std::cout<<"Main Thread ID: "<<std::this_thread::get_id()<<std::endl;
	std::thread T1(RandomFunc, "First");
	std::thread T2(RandomFunc, "Second");
	T1.join();
	T2.join();
	return 0;
}
