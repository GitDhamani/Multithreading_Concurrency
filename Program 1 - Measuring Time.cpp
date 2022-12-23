#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>  //needed for rand() and srand()
#include <ctime>

/*
Program1: Here I lay the foundations of how to benchmark and measure the execution time of a set of tasks. 
I've simulated an algorithm that takes a random amount of time to perform, via the thread sleep method and 
then use the high resolution clock from the chrono library in order to verify this.
*/

void timeThisFunction()
{
	//Seed a new random delay between 1-10 seconds.
   	 srand(time(NULL));
	int num = rand()%10 + 1;
	std::this_thread::sleep_for(std::chrono::seconds(num));
	std::cout<<"The Function took: "<<num<<" seconds."<<std::endl;
}

int main()
{
	//Start time
	auto starttime = std::chrono::high_resolution_clock::now();

	//"Processing"
	timeThisFunction();

	//Stop Time
	auto stoptime = std::chrono::high_resolution_clock::now();
	
	//Duration
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stoptime - starttime);

	std::cout<<"Your Measured time was: "<<duration.count()<<" seconds.";
	return 0;
}
