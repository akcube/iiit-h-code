#include <bits/stdc++.h>
using namespace std;

typedef vector<set<int>> vsi;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define all(s) s.begin(), s.end()
#define sz(x) (int)(x).size()
#define ff first
#define ss second

set<int> acc_states, all_states;
vvi adj;

int id(int state, vsi &states){
	for(int i=0; i<sz(states); i++)
		if(states[i].find(state) != states[i].end())
			return i;
	return -1;
}

bool equiv(int s, set<int> &sub, vsi &states){
	int rep = *sub.begin();
	if(id(s, states) != id(rep, states)) return false;
	for(int i=0; i<sz(adj[0]); i++)
		if(id(adj[s][i], states) != id(adj[rep][i], states))
			return false;
	return true;
}

vsi recurse(vsi states){
	vsi nstates;
	for(auto &s:all_states){
		bool found = false;
		for(auto &subset:nstates){
			if(equiv(s, subset, states)){
				subset.insert(s);
				found = true;
				break;
			}
		}
		if(!found) nstates.push_back({s});
	}

	if(sz(nstates) == sz(states)) return states;
	else return recurse(nstates);
}

void dfs(int node, vvi &adj){
	if(all_states.find(node) != all_states.end() || node == -1) return;
	all_states.insert(node);

	for(auto &x:adj[node])
		dfs(x, adj);
}

int main(){
    int n, k, a; cin>>n>>k>>a;
    adj.assign(n, vi(26, -1));
    for(int i=0; i<a; i++) {
    	int x; cin>>x;
    	acc_states.insert(x);
    }
    for(int i=0; i<k; i++){
    	int s_1, s_2; char x;
    	cin>>s_1>>x>>s_2;
    	adj[s_1][x-'a'] = s_2;
    }
    dfs(0, adj);

    set<int> rej_states;
	set_difference(all(all_states), all(acc_states), inserter(rej_states, rej_states.begin()));
    vsi simp = recurse({acc_states, rej_states});

    set<int> nacc;
    vvi nadj(sz(simp), vi(26, -1));
    set<pair<int, pair<char, int>>> ntrans;
    for(auto &sub:simp){
    	int rep = *sub.begin();
    	for(auto &x:sub){
    		if(acc_states.find(x) != acc_states.end())
    			nacc.insert(id(rep, simp));
    		char c = 'a'-1;
    		for(auto &to:adj[x]){
    			c++;
    			if(to == -1) continue;
    			ntrans.insert({id(rep, simp), {c, id(to, simp)}});
    		}
    	}
    }
    
    cout<<sz(simp)<<" "<<sz(ntrans)<<" "<<sz(nacc)<<endl;
    for(auto &x:nacc) cout<<x<<endl;
    for(auto &p:ntrans) cout<<p.ff<<" "<<p.ss.ff<<" "<<p.ss.ss<<endl;
}