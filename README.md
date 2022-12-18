# Multithreading_Concurrency
How to Perform Multi-threading and Concurrency in Modern C++.

In this repository I explore how to best make use of the Multithreading and concurrency abilities of Modern C++. 

<b>Program1</b>: Here I lay the foundations of how to benchmark and measure the execution time of a set of tasks. I've simulated an algorithm that takes a random amount of time to perform, via the thread sleep method and then use the high resolution clock from the chrono library in order to verify this.

<b>Program2</b>: Here I implement two tasks executing in series, one after the other to sum the total number of odd and even numbers across a range. The benchmarking process from Program1 verifies it takes about 11 seconds to perform.

<b>Program3</b>: Here I launch each task in its own thread and create a multi-threaded application. Since now the two tasks are performed in parallel we can see the benchmarked performance time drops to 6 seconds. So by sharing the processing across multiple threads we can drastically improve performance and provide low latency.

Program4: Here I tackle the issue of Race Hazards when two or more threads are attempting to modify a critical section of code at the same time. Mutex locking ensures access is provided thread-sequentially, one at a time. This means the entirety of the two tasks are done, but not at the same time.

Program5: The mutex lock in the previous program is blocking, meaning that threads that are not able to acquire the lock fast enough must hold in a waiting pattern until it becomes available. However there are times you want the thread to check if it can acquire the lock and if not, it can be free to attend to other tasks before trying again later. This program shows how to achieve this using the try_lock().

Program6: Here I look at locking multiple mutex objects at once. This comes up in producer/consumer scenarios where you have a thread whose job it is to collect data from other threads which are processing it. To do so, it must lock those mutex objects and access, or consume that data. In this example I have two data threads which are incrementing local variables. The consume thread will then lock the mutex objects in each thread so it can pull and reset the data before unlocking them both again.

Program7: Here I show how to launch multiple threads at once, but synchronise them using conditional variables. This allows a thread to sleep if certain conditions are not met in which case, it will also release any mutex locks it has previously acquired. When the conditions are more favourable and perhaps other threads have finished, the thread can be re-awakened and asked to re-acquire the lock and see if the conditions are now more suitable for it to continue. I use this paradigm in order to ensure that the first thread is always executed before the second thread.
