#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <chrono>

/*
Program 12: This is an example of the Producer/Consumer scenario. The Producer thread is dumping data into a 
shared vector that the Consumer is will eventually pull out and empty. Each time the producer adds new data, 
it informs the Consumer by waking up its thread through the use of a condition variable. If the data stored 
is of sufficient size, the consumer will acquire the mutex lock and drain all of the data out before unlocking 
it again. It will then signal back to the producer that it can fill it with more data if it has any. This way the 
two threads run asynchronously, reading and writing data between them. The key here is the use of the shared 
condition variable and the common mutex object. The consumer first tries to acquire the lock and then enters the 
wait instruction of the condition variable. Here ownership of the mutex is transferred to the condition variable 
(which is why we use the unique_lock) which checks the predicate. If false (in this case the buffer not being of sufficient size) 
then the mutex is released and the thread goes to sleep. In the meantime the Producer thread can then acquire the 
lock and fill the buffer with data before unlocking it and signalling back to the Consumer there is now data in the buffer. 
The Consumer thread then awakens from its slumber and immediately re-acquires the lock and then checks the predicate again. 
This time it finds the buffer with data and proceeds to drain it.
*/

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
