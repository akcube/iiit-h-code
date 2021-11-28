# Q3 

# The components

The client and server used are generic server / client code and more or less from the tutorial. Making them multi-threaded is more or less equivalent to coming up with a thread-safe dictionary & queue container. These are implemented in `src/thread_safe_dict.cpp` and `src/thread_safe_queue.cpp` respectively.

# The implementation

## Dictionary 

The idea here is simple, the class contains a private object of the type of container that it is trying to make thread-safe, i.e., the dictionary simulated by a `vector<pair<bool, string>>`. It also contains a vector of locks corresponding to each individual key. The first element of the pair signifies whether the key exists or not. The second element is the key itself.
Each of the usual insert / update / delete / fetch operations are the same as their normal thread-unsafe counterparts, except that they are now wrapped in between a lock acquire and lock unlock statement. Since each of these locks correspond to multiple keys, modifying multiple **different** keys at the same time is possible.
The STL map structure was **NOT** used because insert / delete operations are **NOT** key independent. They might change the structure of the internal tree structure when inserting key K_1 and hence break a fetch on key K_2 at the same time. 
Now, concat might deadlock as it requires two consecutive lock acquires. `concat 1 2` and `concat 2 1` executing at the same time has high chance of deadlocking. To avoid this, we simply acquire the locks in **minimum** order. The lock for k_1 < k_2 is always obtained first. This ensures no deadlocking occurs. The rest is a generic dictionary implementation.

## Queue

The queue contains the STL container itself in private, a mutex lock and a conditional variable. The operations we care about are `push` and `pop`. `push` is relatively straightforward, simply acquire the lock and push the value to the queue. We are done. `pop` is not so simple. To avoid busy waiting, we must sleep till we have work, then pop from the queue. To do so, we have the following idea.
1. Acquire the lock first. Next, check if the queue is empty. If it is not empty, pop the front element, release the lock and return the element. If it empty, sleep on the conditional variable.
2. In the `push` code, every time a new element is pushed, we `signal` the conditional variable. This signals **exactly** one sleeping thread to wake up and consume this new item. If this element was taken before again, we once again sleep on the conditional variable. This avoids busy waiting.

## Server / Client

Once this is done, maintaining a thread_pool in the server is relatively simple. Push requests into the queue, and in the thread function, pop requests from the queue. Note that because the queue is designed well, it does not busy wait for popping. When a new item is popped, the thread has a new request to receive and handles this connection. In the client side code, we simply generate a new thread for every request and make the request to the server. Handling the dictionary updates / returns are just generic dictionary and case handling code.

## Usage

Run `make` in `/q3`. This will compile both server and client. Running `make server` or `make client` will compile them individually. Run `./server n` to run the server and `./client` to run the client. To test on sample, run `./client < input.txt`