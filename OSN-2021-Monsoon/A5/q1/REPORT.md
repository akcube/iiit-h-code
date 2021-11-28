# Q1

# Components

The different components that we need to simulate here are the labs, the courses and the students. Each lab has its own thread, each student has its own thread and each course has its own thread.

# The implementation

The idea here is pretty simple. After a little analysis, notice that a course changes its state after interaction with only the labs to find a TA. The student changes his state after interaction with only the course. These are the only two interactions we need to concern ourselves with. The idea I've used to implement this is as follows.

## Course - Labs
Each lab has an array of TAs and each TA has it's own lock. When the course is looking for TA's, it goes through the entire lab list and attempts to `trylock` on any of the TAs. If even one works, we have our TA. If none work, we have a decision to make. If none of the TAs were locked already **and** no TAs were available, then the course moves to the `REMOVED` state as no one can take this course. If some of the TAs were locked and none were available to take the course, we might get a free TA later, so check again. This allows us to get at TAs individually at the same time across multiple courses. After the course has finished taking it's tutorial, the course releases the lock corresponding to the TA taking the tutorial. 

## Student - Course
Each student iterates over his three preferences. The idea used is similar to locking of course seats used in the real world. The course begins by always holding its own lock. Only **AFTER** a TA is found and the course is ready to go, does the course release its lock for a short period before acquiring it again. The student thread sleeps on the course lock. The course lock can be acquired by the student thread **only** under 2 conditions.
1. The course has got a TA and is looking for students to register.
2. The course has been removed.
In the first case, the student checks if there is space left. If space exists for him (while holding the lock), he increments the number of occupied slots and he goes to sleep on the `finished` conditional variable in the course struct. This is the variable that is signalled when the course tutorial finishes. If he doesn't have space, he doesn't increment the variable but still sleeps on the variable just so he can wake up and check for availability again only **after** the tutorial is done. This avoids busy waiting. Now, if he is able to register himself, he wakes up after the tutorial is done and decides if he wishes to confirm his choice. If yes, he exits. If no, he moves to his next preference.
If the course was removed, he increments preference. The course thread releases its own lock forever just after it moves to the `REMOVED` state.

## Usage

Run `make` in `/q1` and run `./q1`. If you wish to test on sample, run `./q1 < input.txt`