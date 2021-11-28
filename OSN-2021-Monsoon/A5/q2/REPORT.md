# Q2

# Components

The different components that we need to simulate here are the three different zones, an individual spectator and the game itself. Each zone has its own thread. Each spectator has his own thread. Each group has its own thread and finally, there is another thread which simulates the game.

# The implementation

The idea here is pretty simple. After a little analysis, notice that the match simulation which contains info such as the game score, who scored and it's chances etc. only depends on the goal chances we read as input. These chances were read as input in `GoalInfo` structs. In `matchsim.c`, we simply evaluate the chance and give the team a goal if we think they had a high chance of scoring. 

The state of the game is mentioned in a global `Match` struct called `MatchInfo`. Reads / writes to this struct must be atomic and is hence protected with a lock. We use the "conditional timed wait" to make sure all the goal evaluations are done without busy waiting at the right times.

Now, each `Zone` struct contains a semaphore. This is the number of free seats in that zone at any point of time. The reasoning for why this would be useful is obvious.

To simulate spectators, we have the following logic. If the spectator is in a "waiting for seats" state, he tries a `sem_trywait` on all the zones he is allowed to avail a seat in. If any of these succeed, he has his seat. However, if all of them fail, he **must** wait. To wait, he performs a "conditional timed wait" on one of three global conditional variables.
1. Home fans - HN
2. Away fans - A
3. Neutral fans - HAN
Each of these conditional variables are signalled when a zone in its subset obtains a free seat. That is, HN is signalled when either H or N gets a free seat.
This conditional timed wait checks for either timeout (which signifies leaving due to impatience) or a `sem_trywait` to succeed, which implies we have a seat.

Now, once the spectator is spectating, we must wait for `X` time to pass or leave if the team is performing poorly. We check this as follows:
1. First check if the team has already done poorly, if yes, quit.
2. If no, we do a "conditional timed wait" on a conditional variable which is signalled **every** time the opponent team scores a goal. If this wait times out, the player leaves after spectating. Otherwise, he checks if the opponent score is >= R again. That is, go back to step 1 and repeat.
By doing so, we have successfully avoided busy waiting. This signalling is done in the matchsim thread.
When a spectator leaves, he signals the conditional variable(s) HAN, HN or A that he is freeing up to ensure other waiting spectators can get their seats.

## Bonus

This is pretty simple as well. The group struct has a semaphore associated with it. When a person leaves the stadium, we simply post to the semaphore. The thread simulating the group waits on this semaphore. Everytime is increments, it increments it's local counter. When this counter equals group size, the group leaves as a whole.

## Usage

Run `make` in `/q2` and run `./q2`. If you wish to test on sample, run `./q2 < input.txt`