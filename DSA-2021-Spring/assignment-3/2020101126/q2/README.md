## Dictionary 

These are the following values I obtained

P = 32 => 0.39

P = 33 => 0.40

For a non prime table size.

For prime table size, I obtained

P = 32 => 0.38

P = 33 => 0.37

Finally I changed the initial constant from 0 to 5381 (as used in the famous DJB2 hash and got the following results)

P = 32 => 0.38

P = 33 => 0.35

### Conclusion

We observe that for a prime table size, using powers of 2 such as 32 are not great at giving good distributions and we can do much better using prime values for p such as 33. This difference is only expected to grow in magnitude for larger and larger n.

Further it is to be noted that a table size which is also a power of two along with p=32 would perform very poorly as the modulo can divide p and will make most of the hash redundant.



#### Side note to the TA:

Observations were taken using horners rule and separate chaining for the question. However the actual implementation used for OJ uses a hashtable I spent a good amount of time optimizing. It uses murmur hash and several bitwise operations to speed up i/o read and hashing. One of these operations involves casting a `char*` to `uint64_t`. This is reasonable operation and does not require alignment to 8 byte boundaries. However `fsanitize=ubsan` throws up an error for this. A little googling showed that this was more a warning than an error.  This is not undefined behavior.

So I hope this is alright.



