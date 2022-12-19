#include <iostream>
#include <thread>
#include <mutex>
#include <future>

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
