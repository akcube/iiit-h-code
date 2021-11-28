#include <bits/stdc++.h>

using namespace std;

template <class T>
class thread_safe_queue {

public:
	thread_safe_queue(){
		pthread_mutex_init(&lock, NULL);
		pthread_cond_init(&wakeup, NULL);
	}

	~thread_safe_queue(){
		pthread_mutex_destroy(&lock);
		pthread_cond_destroy(&wakeup);
	}

	T pop(){
		T ret;
		bool found = false;
		pthread_mutex_lock(&lock);
		while(found == false){
			if(!q.empty()){
				found = true;
				ret = q.front();
				q.pop();
			}
			if(!found)
				pthread_cond_wait(&wakeup, &lock);
		}
		pthread_mutex_unlock(&lock);
		return ret;
	}

	void push(T val){
		pthread_mutex_lock(&lock);
		q.push(val);
		pthread_cond_signal(&wakeup);
		pthread_mutex_unlock(&lock);
	}

private:
	queue<T> q;
	pthread_mutex_t lock;
	pthread_cond_t wakeup;
};
