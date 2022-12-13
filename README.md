# Multithreading_Concurrency
How to Perform Multi-threading and Concurrency in Modern C++.

Ever since C++11 (C++0x), the C++ language has had support for multithreading and concurrency and has needed to rely less on platform APIs to perform true task switching. Modern hardware is more equipped these days to handle the demands of a well designed multithreaded application, especially on multi-core CPUs. 

The dangers with launching multiple threads and keeping track of them can be unweidy, things from managing the contextual overhead to containing the risk of shared access to common data as the threads race each other to modify it. Thankfully you can more or less manage such race conditions through the use of mutex objects and lock guards to ensure sequential access when you need it. In this repository I show examples of how to employ multithreading and concurrency, including how a triple threaded application can perform parallel tasking across separate threads and then benchmark the performance. 

In the first example we have a standard single threaded application with two tasks to perform. Performing them sequentially takes X seconds.
In the second example we improve upon this by launching separate threads for each task so that they can occur concurrently. We then allow them both to finish and rejoin the main thread. Benchmarking this shows how much faster we're able to produce the result, a full X seconds faster just by exploiting the ideas of multi-threading and concurrency.

Multithreading and Concurrency in C++ is an entire topic of its own, but very valuable to the modern C++ software engineer.
