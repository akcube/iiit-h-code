#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<vii> vvii;
#define ff first
#define ss second
#define pb push_back
#define all(s) s.begin(), s.end()
#define sz(x) (int)(x).size()
#define file_read(x,y) freopen(x, "r", stdin); \
                    freopen(y, "w", stdout);

vector<vector<int>> adj;

class NFA {

public:
    NFA(){
        m=1;
        adj.resize(2);
    }
    ~NFA() = default;

    pii concat(pii s, pii t){
        add(s.ss, t.ff, 'E');
        if(s.ss == AC) AC = t.ss;
        return {s.ff, t.ss};
    }

    pii addnew(char x){
        add(m, m+1, x);
        m += 2;
        return {m-2, m-1};
    }

    pii unify(pii a, pii b){
        int s = m;
        int t = m+1;
        add(s, a.ff, 'E');
        add(s, b.ff, 'E');
        add(a.ss, t, 'E');
        add(b.ss, t, 'E');
        m += 2; 
        if(a.ff == start || b.ff == start) start = m-2;
        if(a.ss == AC || b.ss == AC) AC = m-1;
        return {m-2, m-1};
    }

    pii kleen(pii a){
        int st = m++;
        add(st, a.ff, 'E');
        add(a.ss, st, 'E'); // Will account for empty string
        if(a.ff == start) start = m-1;
        if(a.ss == AC) AC = m-1;
        return {m-1, m-1};
    }

    void finish() { add(0, start, 'E'); }
    int size() { return (int) all_states.size(); }
    int acc_size() { return 1; }
    int trans_size() {
        int ct = 0;
        for(auto &vec:adj) ct += sz(vec);
        return ct;
    }
    int AC_state() { return AC; }
    int start_state() { return 0; }
    void print_trans(){
       for(int i=0; i<sz(adj); i++)
            for(auto &p:adj[i])
                cout<<i<<" "<<p.ss<<" "<<p.ff<<endl;
    }

private:
    vector<vector<pair<int, char>>> adj;
    int m, start = 1, AC = 2;
    set<int> all_states;
    
    void add(int s, int t, char trans){
        if(sz(adj) < max(s+1, t+1)) adj.resize(max(s, t) + 1);
        adj[s].pb({t, trans});
        all_states.insert(s);
        all_states.insert(t);
    }
};

template<class T>
bool in(T x, set<T> S){
    return S.find(x) != S.end();
}

bool isOP(char x){
    switch(x){
        case '(':
        case ')':
        case '+':
        case '*':
        case '.':
            return true;
        default:
            return false;
    }
}

string inftopos(string infix){
    string ret = "";
    int p[48]; p['('] = 1; p['+'] = 2; p['.'] = 3; p['*'] = 4;
    vector<char> bt;

    for(auto &c:infix){
        if(!isOP(c)) ret += c;
        else{
            switch(c){
                case '(':
                    bt.pb(c);
                break;
                case ')':
                    for(; !bt.empty() && bt.back() != '('; bt.pop_back())
                        ret += bt.back();
                    bt.pop_back();
                break;
                default:
                    for(; !bt.empty() && p[c] <= p[bt.back()]; bt.pop_back())
                        ret += bt.back();
                    bt.pb(c);
                break;
            }
        }
    }
    for(; !bt.empty(); bt.pop_back()) ret += bt.back();
    return ret;
}

int main(int argc, char *argv[]){

    if(argc != 3){
        cout<<"Usage ./q4 [infile] [outfile]"<<endl;
        return -1;
    }

    file_read(argv[1], argv[2]);

    string regex; cin>>regex;
    int n = sz(regex);
    string infix = "";

    set<char> endterm = {')', '*'};
    set<char> startterm = {'{'};
    for(int i=0; i<n; i++){
        infix += regex[i];
        if((in(regex[i], endterm) || isalpha(regex[i])) && i+1 < n && (in(regex[i+1], startterm) || isalpha(regex[i+1])))
            infix += '.';
    }

    NFA nfa;
    string pfix = inftopos(infix);
    vii tracker;
    pii last, last2;
    for(auto &ch:pfix){
        switch(ch){
            case '.':
                last = tracker.back(); tracker.pop_back();
                last2 = tracker.back(); tracker.pop_back();
                tracker.pb(nfa.concat(last2, last));
            break;
            case '+':
                last = tracker.back(); tracker.pop_back();
                last2 = tracker.back(); tracker.pop_back();
                tracker.pb(nfa.unify(last2, last));
            break; 
            case '*':
                last = tracker.back(); tracker.pop_back();
                tracker.pb(nfa.kleen(last));
            break;
            default:
                tracker.pb(nfa.addnew(ch));
        }
    }

    nfa.finish();
    cout<<nfa.size()<<" "<<nfa.trans_size()<<" "<<nfa.acc_size()<<endl;
    cout<<nfa.AC_state()<<endl;
    nfa.print_trans();

}