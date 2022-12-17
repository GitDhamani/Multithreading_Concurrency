# Multithreading_Concurrency
How to Perform Multi-threading and Concurrency in Modern C++.

Ever since C++11 (C++0x), the C++ language has had support for multithreading and concurrency and has needed to rely less on platform APIs to perform true task switching. Modern hardware is more equipped these days to handle the demands of a well designed multithreaded application, especially on multi-core CPUs. 

The dangers with launching multiple threads and keeping track of them can be unweidy, things from managing the contextual overhead to containing the risk of shared access to common data as the threads race each other to modify it. Thankfully you can more or less manage such race conditions through the use of mutex objects and lock guards to ensure sequential access when you need it. In this repository I show examples of how to employ multithreading and concurrency, including how a triple threaded application can perform parallel tasking across separate threads and then benchmark the performance. 

Starting with Program 1 we look at how to measure the time taken for an algorithm to perform. In this case we're simulating processing time with the thread sleep method which pauses the thread for a random amount of time between 1-10 seconds.
This is so that we know roughly how long the "algorithm" takes. Then we use the high precision clock to measure out how long the algorithm takes ourselves so we can do a comparison. So here we're just simply getting used to measuring time and laying the foundations of being able to show how much faster a multi-threaded application will be in the next phase. Here is the typical output:

The Function took: 5 seconds.  
Your Measured time was: 5 seconds.

In Program 2 we are doing some actual processing. We're counting all the odd and even numbers up to a fairly large number only being capable of held in an unsigned long long integer variable. This guarantees we should get a fairly significant amount of processing time of a few seconds. So we've replaced the thread sleep with two individual functions, one to count odd numbers and the other to count even. They are really only checking the least significant bit of the number to determine this. We measure how long the tasks take to complete in totality. On my 2.5Ghz CPU it takes approximately 11 seconds to complete. Typical program output:

Odd Count: 902500000000000000  
Even Count: 902499999050000000  
Your Measured time was: 11 seconds.

In Program 3 we now implement multi-threading and run each function in its own separate thread, so they execute in parallel. This now means both processes are running concurrently and we see the time now taken to complete both tasks is drastically reduced by 50%. Typical program output:

Even Sum: 902499999050000000  
Odd Sum: 902500000000000000  
Your Measured time was: 6 seconds.

So by exploiting the ideas of multithreading and concurrency we are experiencing double the speed of execution. We've achieved the same task as earlier (counting the sum of even and odd numbers) but reduced the time by almost half just through the implementation of Multiple threads. 

Multithreading and Concurrency in C++ is an entire topic of its own, but very valuable to the modern C++ software engineer.
