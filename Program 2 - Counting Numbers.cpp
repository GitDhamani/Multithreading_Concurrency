#include <iostream>
#include <chrono>

void countOdd()
{
	unsigned long long oddcount {};
	for (unsigned long long i = 0; i<1900'000'000; i++)
	if ((i & 1) == 1) oddcount += i;
	std::cout<<"Odd Sum: "<<oddcount<<std::endl;
}

void countEven()
{
	unsigned long long evencount {};
	for (unsigned long long i = 0; i<1900'000'000; i++)
	if ((i & 1) == 0) evencount += i;
	std::cout<<"Even Sum: "<<evencount<<std::endl;
}

int main()
{
	//Start time
	auto starttime = std::chrono::high_resolution_clock::now();
	
	//Counting Odd Numbers
	countOdd();

	//Counting Even Numbers
	countEven();
	
	//Stop Time
	auto stoptime = std::chrono::high_resolution_clock::now();
	
	//Duration
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stoptime - starttime);
	std::cout<<"Your Measured time was: "<<duration.count()<<" seconds.";

	return 0;
}