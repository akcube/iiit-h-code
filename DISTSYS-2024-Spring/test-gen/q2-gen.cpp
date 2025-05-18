#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
using ll = long long;
using dbl = long double;
//#define int ll

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvii = vector<vii>;
using vll = vector<ll>;

#define ff first
#define ss second
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define tc int t; cin>>t; while(t--)
#define fightFight cin.tie(0) -> sync_with_stdio(0)

void solve(){
	auto rng = std::mt19937(std::random_device()());
	const int MXN = 1e3, MXM = 1e4;
	
	int n = rng() % MXN + 1, m = rng() % MXM + 1;
	cout << n << ' ' << '\n';
	vii edges;
	while(sz(edges) != m){
		while(sz(edges) < m)
			edges.emplace_back(rng() % n + 1, rng() % n + 1);
		sort(all(edges));
		edges.resize(unique(all(edges)) - edges.begin());
	}
	vvi adj(n);
	for(auto &[u, v] : edges) adj[u-1].pb(v-1), adj[v-1].pb(u-1);
	for(int v=0; v < n; v++){
		cout << v+1 << "\t";
		for(auto &to : adj[v]) cout << to+1 << " ";
		cout << '\n';
	}
}

signed main(){ 
	fightFight; 
	solve(); 
}
