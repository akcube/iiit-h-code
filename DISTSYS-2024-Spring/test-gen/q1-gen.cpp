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
	for(auto &[u, v] : edges) cout << u << " " << v << '\n';
}

signed main(){ 
	fightFight; 
	solve(); 
}
