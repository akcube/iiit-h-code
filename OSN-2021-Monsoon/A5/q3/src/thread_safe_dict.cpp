#include <bits/stdc++.h>

using namespace std;

template <class Key, class T>
class thread_safe_map {

public:
	thread_safe_map() = default;
	thread_safe_map(int n){
		locks.resize(n);
		arr.assign(n, {false, ""});
		for(auto &x:locks) pthread_mutex_init(&x, NULL);
	}
	~thread_safe_map(){
		for(auto &x:locks) pthread_mutex_destroy(&x);
	}

	void resize(int n){
		arr.assign(n, {false, ""});
		for(auto &x:locks) pthread_mutex_destroy(&x);
		locks.resize(n);	
		for(auto &x:locks) pthread_mutex_init(&x, NULL);
	}

	bool update_t(Key k, T val){
		bool ret = true;
		pthread_mutex_lock(&locks[k]);
		if(arr[k].first != true) ret = false;
		else arr[k].second = val;
		pthread_mutex_unlock(&locks[k]);
		return ret;
	}

	bool insert_t(pair<Key, T> val){
		bool ret = true;
		pthread_mutex_lock(&locks[val.first]);
		if(arr[val.first].first == true) ret = false;
		else arr[val.first] = {true, val.second};
		pthread_mutex_unlock(&locks[val.first]);
		return ret;
	}

	pair<bool, string> cat_t(Key ff, Key ss){
		if(ff == ss) return {false, ""};
		
		T ff_val, ss_val;
		Key lff = ff, lss = ss;
		bool ret = true;
		string ret_str = "";

		if(lff > lss) swap(lff, lss);

		pthread_mutex_lock(&locks[lff]);
		pthread_mutex_lock(&locks[lss]);
		if(!arr[ff].first || !arr[ss].first) ret = false;
		else{
			ff_val = arr[ff].second;
			ss_val = arr[ss].second;
			arr[ff].second = ff_val + ss_val;
			arr[ss].second = ss_val + ff_val;
			ret_str = arr[ss].second;
		}
		pthread_mutex_unlock(&locks[lss]);
		pthread_mutex_unlock(&locks[lff]);
		return {ret, ret_str};
	}

	bool erase_t(Key k){
		bool ret = true;
		pthread_mutex_lock(&locks[k]);
		if(arr[k].first == false) ret = false;
		else arr[k] = {false, ""};
		pthread_mutex_unlock(&locks[k]);
		return ret;
	}

	T read_t(Key k){
		pthread_mutex_lock(&locks[k]);
		T val = arr[k].second;
		pthread_mutex_unlock(&locks[k]);
		return val;
	}

	bool exists(Key k){
		bool ret;
		pthread_mutex_lock(&locks[k]);
		ret = arr[k].first;
		pthread_mutex_unlock(&locks[k]);
		return ret;
	}

private:
	vector<pthread_mutex_t> locks;
	vector<pair<bool, string>> arr;
};