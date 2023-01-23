#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

/*
Program 7: Here I show how to launch multiple threads at once, but synchronise them using conditional variables. 
This allows a thread to sleep if certain conditions are not met in which case, it will also release any mutex locks it 
has previously acquired. When the conditions are more favourable and perhaps other threads have finished, the thread can 
be re-awakened and asked to re-acquire the lock and see if the conditions are now more suitable for it to continue. 
I use this paradigm in order to ensure that the first thread is always executed before the second thread.

So in this case, we have started thread2 first and so in all likelyhood start2 will execute first. Which we actually don't want. 
It will acquire the mutex lock on m1. But then cv.wait will check the status if the boolean variable correctStart which has been initialised 
to zero. If it is zero, then it will unlock the mutex and put its current thread to sleep because it knows it shouldn't be executing first now.

So now start1 can execute, do what it needs to and then when it's finished it will release the lock, set the boolean valuable to true and 
sent a notification to the condition variable to wake up its thread and try again. Notify_one means the notification is sent out to only a
single waiting thread, which is decided not by you but by the OS. Notify_all would have sent notifications to all waiting threads.

So the conditional variable in start2 wakes up its thread and checks the state of correctStart and this time finds it to be true. 
So it re-acquires the lock and starts its task before releasing the lock on the way out.

So in this way we have forced the sequence so that start1 executes first then start2.
*/

std::mutex m1;
std::condition_variable cv;
bool correctStart{};

void start1()
{
	m1.lock();
	std::cout<<"Start1 Executed."<<std::endl;
	m1.unlock();
	correctStart = true;
	cv.notify_one();
}

void start2()
{
	std::unique_lock<std::mutex> mtx(m1);
	cv.wait(mtx, [](){ return correctStart; });
	std::cout<<"Start2 Executed."<<std::endl;
	m1.unlock();
}

int main()
{
	std::thread worker2(start2);
	std::thread worker1(start1);
	worker2.join();
	worker1.join();
	return 0;
}
