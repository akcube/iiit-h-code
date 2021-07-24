## HashTable Load Analysis
The following document will contain my analysis for hashtable load and search for 3 different methods of collision resolution.

1. Separate Chaining
2. Linear Probing
3. Quadratic Probing

The approach is as follows. We will insert 2000 random elements into a hash table of size 2003 using the identity hash and record relevant information such as runtime, avg no of probes, etc. at alpha values 0.1, 0.2, 0.3, 0.4, 0.5, 0.7 and 0.9.

### Separate Chaining

The insertion time for separate chaining would be much faster if we inserted at the beginning of each linked list instead of at the end. This would ensure constant O(1) insertion at all times and no extra probing to find an empty spot. However we are required to insert at the end and hence we can then analyze the avg. number of probes required. 

### Linear Probing

Nothing special to note, the insertion function was modified slightly to return the avg number of probes and the data was collected in main.c

### Quadratic Probing

We must rehash the table at alpha >= 0.5 and hence we cannot have readings for alpha >= 0.5. But the approach taken was similar to Linear probing.

### Results 


|Alpha|Linear Probing|Quadratic Probing|Separate Chaining|
|------|------|------|------|
|0.1|0.09| 0.06 |0.06|
|0.2|0.24| 0.14 |0.16|
|0.3|0.31| 0.29 |0.21|
|0.4|0.93| 0.75 |0.46|
|0.5|1.46||0.52|
|0.6|1.98||0.63|
|0.7|5.26||0.71|
|0.8|12.31||0.76|
|0.9|41.34||0.81|

The average number of probes to insert in linear probing increases exponentially as alpha increases as primary clustering becomes a very very difficult hurdle for linear probing beat making the last few insertions near O(n).

Quadratic probing on the other hand keeps load factor fairly low at the only expense of rehashing using table doubling. This is amortized to O(1) and hence keeps the insertions at a constant O(k) while still guaranteeing great cache locality so that we have fewer cache misses during search.

Separate chaining gives us the least number of probes required at the expense of terrible cache locality.

We can expect linear probing to perform poorly while separate chaining and quadratic probing perform fairly competitively. We can truly expect to see quadratic probing shine when performing search queries where the lesser number of cache misses will definitely play a much bigger role in determining who the faster method is.

### Hash Table Time Readings

### Separate Chaining
Average Time Taken: 1.40ms

With garbage array: 10.68ms

### Linear Probing 
Average Time Taken: 5.88ms

With garbage array: 14.68ms

### Quadratic Probing
Average Time Taken: 1.79ms

With garbage array: 8.48ms

We can see that out of the three collision resolution methods for insertion, separate chaining is the fastest. Plus we know that inserting at the beginning can make it even faster. It is great for insertion. Rehashing slows down quadratic probing just enough to let separate chaining win. But given a start table size thats much larger than 'n' and accounting in search time, we can definitely expect quadratic probing to win. 

Quadratic probing pagefault 53 times on average vs 72 times for separate chaining. Linear probing is at 50. But the huge cluster size is a pretty harsh counter that pulls linear probing down.

Despite separate chaining being faster here I expect quadratic probing to be the fastest overall hashtable thanks to its great cache locality and amortized rehashing time which will only make it better and better for larger and larger N

Further adding the garbage array significantly slows down all the methods as the number of pagefaults increases dramatically. It is interesting to note that this fragments heap memory more and hence causes separate chaining to lose to quadratic probing. Although the array size is large linear (well quadratic) access ensures that we are able to prefetch from cache during our probes