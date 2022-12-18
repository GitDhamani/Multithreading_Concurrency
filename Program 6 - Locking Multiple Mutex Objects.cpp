#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1, m2;
int x{0}, y{0}, sum{0};

void dataX()
{
	for (int i = 0; i<5; i++)
	{
		m1.lock();
		x++;
		std::cout<<"X updated to: "<<x<<std::endl;
		m1.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void dataY()
{
	for (int i = 0; i<5; i++)
	{
		m2.lock();
		y++;
		std::cout<<"Y updated to: "<<y<<std::endl;
		m2.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void consume()
{
	int loopnum{5};
	while(true)
	{
		int rtn = std::try_lock(m1, m2);
		if (rtn == -1)
		{			
			if (x!=0 && y!=0)
			{
				sum += x + y;
				std::cout<<"Sum updated to: "<<sum<<std::endl;
				x = y = 0;
				loopnum--;
			}
			m1.unlock();
			m2.unlock();
		}
		if (loopnum == 0) break;
	}
}

int main()
{
	std::thread worker1(dataX);
	std::thread worker2(dataY);
	std::thread worker3(consume);
	
	worker1.join();
	worker2.join();
	worker3.join();
	return 0;
}
