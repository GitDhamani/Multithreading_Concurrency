#include <iostream>
#include <thread>
#include <mutex>
#include <future>

/*
Program 10: Here I am making use of the Promise and Future Objects in order to extract data from a working thread 
before it finishes. So this might be during a case where a thread has processed a value that you need in another thread. 
In that case you pass a promise object into the thread constructor as a parameter to the function to be launched. It will 
then modify it to fill it with a value. Back in the main thread, a Future object has been created from the Promise object 
and can now query to see if the value has been populated, or wait until it is. This then allows transfer of information between threads.
*/

void Func(std::promise<unsigned long long>&& prom)
{
	unsigned long long sum;
	for (int i = 0; i<1'900'000'000; i++)
		if((i&1) == 1) sum+=i;
	
	prom.set_value(sum);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout<<"Thread Finished"<<std::endl;
}

int main()
{
	std::promise<unsigned long long> prom;
	std::future<unsigned long long> future = prom.get_future();
	std::thread Worker1(Func, std::move(prom));
	std::cout<<"The Value of the Promise is: "<<future.get()<<std::endl;
	Worker1.join();
	return 0;
}
