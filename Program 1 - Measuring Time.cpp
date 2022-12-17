#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>  //needed for rand() and srand()
#include <ctime>

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