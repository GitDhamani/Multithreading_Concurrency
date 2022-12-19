#include <iostream>
#include <thread>
#include <mutex>
#include <string>

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
