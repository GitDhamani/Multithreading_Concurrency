#include <iostream>
#include <chrono>
#include <thread>

/*
Program3: Here I launch each task in its own thread and create a multi-threaded application. 
Since now the two tasks are performed in parallel we can see the benchmarked performance time drops to 6 seconds. 
So by sharing the processing across multiple threads we can drastically improve performance and provide low latency.
*/

void countOdd()
{
	unsigned long long oddcount {};
	for (unsigned long long i = 0; i<1900000000; i++)
	if ((i & 1) == 1) oddcount += i;
	std::cout<<"Odd Sum: "<<oddcount<<std::endl;
}

void countEven()
{
	unsigned long long evencount {};
	for (unsigned long long i = 0; i<1900000000; i++)
	if ((i & 1) == 0) evencount += i;
	std::cout<<"Even Sum: "<<evencount<<std::endl;
}

int main()
{
	//Start time
	auto starttime = std::chrono::high_resolution_clock::now();
	
	//Create and Launch Threads
	std::thread worker1(countOdd);
	std::thread worker2(countEven);
	
	//Wait for Threads to Rejoin Main Thread
	worker1.join();
	worker2.join();
	
	//Stop Time
	auto stoptime = std::chrono::high_resolution_clock::now();
	
	//Duration
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stoptime - starttime);
	std::cout<<"Your Measured time was: "<<duration.count()<<" seconds.";

	return 0;
}
