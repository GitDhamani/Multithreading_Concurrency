# Multithreading_Concurrency
How to Perform Multi-threading and Concurrency in Modern C++.

In this repository I explore how to best make use of the Multithreading and concurrency abilities of Modern C++. 

<b>Program1</b>: Here I lay the foundations of how to benchmark and measure the execution time of a set of tasks. I've simulated an algorithm that takes a random amount of time to perform, via the thread sleep method and then use the high resolution clock from the chrono library in order to verify this.

<b>Program2</b>: Here I implement two tasks executing in series, one after the other to sum the total number of odd and even numbers across a range. The benchmarking process from Program1 verifies it takes about 11 seconds to perform.

<b>Program3</b>: Here I launch each task in its own thread and create a multi-threaded application. Since now the two tasks are performed in parallel we can see the benchmarked performance time drops to 6 seconds. So by sharing the processing across multiple threads we can drastically improve performance and provide low latency.

<b>Program4</b>: Here I tackle the issue of Race Hazards when two or more threads are attempting to modify a critical section of code at the same time. Mutex locking ensures access is provided thread-sequentially, one at a time. This means the entirety of the two tasks are done, but not at the same time.

<b>Program5</b>: The mutex lock in the previous program is blocking, meaning that threads that are not able to acquire the lock fast enough must hold in a waiting pattern until it becomes available. However there are times you want the thread to check if it can acquire the lock and if not, it can be free to attend to other tasks before trying again later. This program shows how to achieve this using the try_lock().

<b>Program6</b>: Here I look at locking multiple mutex objects at once. This comes up in producer/consumer scenarios where you have a thread whose job it is to collect data from other threads which are processing it. To do so, it must lock those mutex objects and access, or consume that data. In this example I have two data threads which are incrementing local variables. The consume thread will then lock the mutex objects in each thread so it can pull and reset the data before unlocking them both again.

<b>Program7</b>: Here I show how to launch multiple threads at once, but synchronise them using conditional variables. This allows a thread to sleep if certain conditions are not met in which case, it will also release any mutex locks it has previously acquired. When the conditions are more favourable and perhaps other threads have finished, the thread can be re-awakened and asked to re-acquire the lock and see if the conditions are now more suitable for it to continue. I use this paradigm in order to ensure that the first thread is always executed before the second thread.

<b>Program8</b>: Here I mischieviously try and create a deadlock, where the two threads get stuck waiting for each other in an endless tug of war. The two threads launch FuncA and FuncB respectively. However FuncA locks mutex M1 and M2 in that order, and FuncB locks mutex M2 and M1 and in that order. So what tends to happen is either function will obtain the first lock without any issue but will then halt whilst trying to acquire the second lock. However acquiring that lock will not be possible as the other thread has already obtained it, hence the deadlock.

<b>Program9</b>: Here I take the deadlock from the last Program and show how to avoid it using std::lock(). This is an interesting multi-mutex locking mechanism and will continuously try to lock and unlock all the mutex objects you pass in to it. If successful it will lock all the mutex object parameters, otherwise it will unlock any acquired mutex locks and wait on any specific one it has had trouble with. This means both threads are now trying to lock the same two mutex objects at the same time, but through the use of std::lock(), there are no deadlocks.

<b>Program10</b>: Here I am making use of the Promise and Future Objects in order to extract data from a working thread before it finishes. So this might be during a case where a thread has processed a value that you need in another thread. In that case you pass a promise object into the thread constructor as a parameter to the function to be launched. It will then modify it to fill it with a value. Back in the main thread, a Future object has been created from the Promise object and can now query to see if the value has been populated, or wait until it is. This then allows transfer of information between threads.

<b>Program11</b>: Here is where I distinguish which thread has actually acquired the mutex lock on the critical sections by pulling its Thread ID. It seems in general the main thread has the ID of 1, and then every new thread created goes up sequentially.

<b>Program12</b>: This is an example of the Producer/Consumer scenario. The Producer thread is dumping data into a shared vector that the Consumer is keeping an eye on. Each time the producer adds new data, it informs the Consumer by waking up its thread through the use of a condition variable. If the data stored is of sufficient size, the consumer will acquire the mutex lock and drain all of the data out before unlocking it again. This way the two threads run asynchronously, reading and writing data.
