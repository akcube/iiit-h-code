#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<vi> vii;

#define f first
#define s second
#define pb push_back
#define mp make_pair
#define loop(n) for(int i=0; i<n; i++)
#define rep(i, a, n) for(int i=a; i<n; i++)
#define file_read freopen("input.txt", "r", stdin); \
				  freopen("output.txt", "w", stdout);
#define tc int t; cin>>t; while(t--)
#define endl "\n"
#define usainbolt cin.tie(0) -> sync_with_stdio(0)

int main(void){
	usainbolt;
	//file_read
	
	int q;
	cin>>q;
	multiset<int> s;
	for(int i=0; i<q; i++){
		string query;
		int x;
		cin>>query;
		if(query=="Push"){
			cin>>x;
			s.insert(x);
		}
		else if(query=="Diff"){
			if(s.empty()){
				cout<<-1<<endl;
				continue;
			}
			cout<<abs((*s.begin())-(*s.rbegin()))<<endl;
			if((*s.begin())==(*s.rbegin())){
				s.erase(s.begin());
			}
			else{
				s.erase(s.begin());
				s.erase(*(s.rbegin()));	
			}
		}
		else if(query=="CountHigh"){
			if(!s.empty())
				cout<<s.count(*s.begin())<<endl;
			else
				cout<<-1<<endl;
		}
		else if(query=="CountLow"){
			if(!s.empty())
				cout<<s.count(*s.rbegin())<<endl;
			else 
				cout<<-1<<endl;
		}
	}

}