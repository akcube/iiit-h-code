#include<iostream>
#include<bits/stdc++.h>

using namespace std;

typedef struct transition
{
    int curr;
    char c;
    int next;
}transition;


void findreachable(int a, int* rechable, int* visited, int ** &transition){
    visited[a] = 1;
    for(int i = 0; i < 26; i++){
        if(transition[a][i] != -1 && visited[transition[a][i]] == 0){
            findreachable(transition[a][i], rechable, visited, transition);
        }
    }
    rechable[a] = 1;

}

bool check(int state, int reference, vector<set<int>> equivalence,int ** &transition){

    int findset;
    int findreference;
    for(int i = 0; i < 26; i++){
        for (int j= 0; j<equivalence.size(); j++){
            if(equivalence[j].find(transition[state][i]) != equivalence[j].end()){
                findset = j;
            }
            if(equivalence[j].find(transition[reference][i]) != equivalence[j].end()){
                findreference = j;
            }
        }
        if(findset != findreference){
            return false;
        }

    }
    return true;
}

vector<set<int>> equivalencetheorem (vector<set<int>> equivalence,  int ** &transition){
    vector<set<int>> newequivalence;

    for (auto it = equivalence.begin(); it != equivalence.end(); it++){

        for (auto it2 = it->begin(); it2 != it->end(); it2++){
            bool flag = true;
            for(int i=0; i<newequivalence.size();i++){
                if(newequivalence[i].find(*it2) != newequivalence[i].end()){
                    flag = false;
                    break;
                }
            }
            if(flag){
                set<int> newset;
                newset.insert(*it2);

                for(auto it3 = it->begin(); it3 != it->end(); it3++){
                    bool flag2 = true;
                    for(int j=0; j<newequivalence.size();j++){
                        if(newequivalence[j].find(*it3) != newequivalence[j].end()){
                            flag2 = false;
                            break;
                        }
                    }
                    if(flag2){

                        if(check(*it3, *it2, equivalence, transition)){
                            newset.insert(*it3);
                        }
                    }
                }
                newequivalence.push_back(newset);
            }
        }
    }
    if (newequivalence.size() == equivalence.size()){
        return newequivalence;
    }
    else{
        return equivalencetheorem(newequivalence, transition);
    }


}



int main(){


    int startstate = 0;
    int n,k,a;
    cin>>n>>k>>a;
    set<int> final_states;
    set<int> non_final_states;
    int state;
    for (int i = 0; i < a; i++)
    {
        cin>>state;
        final_states.insert(state);
    }
    for(int i = 0; i < n; i++){
        if(final_states.find(i) == final_states.end()){
            non_final_states.insert(i);
        }
    }


    int **transitionMap = (int**)malloc(n*sizeof(int*));
	for (int i = 0; i < n; i++){
		transitionMap[i] = (int*) malloc(26*sizeof(int));
		for (int j = 0; j < 26; j++){
			transitionMap[i][j] = -1;
		}
	}



    for (int i = 0; i < k; i++)
    {
        int x,z;
        char y;
        cin>>x>>y>>z;
        transitionMap[x][y-'a'] = z;
    }

    int *visited = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }

    int *rechable = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        rechable[i] = 0;
    }

    findreachable(startstate, rechable, visited, transitionMap);

    for(int i = 0; i<n; i++){
        if(rechable[i]==0)
        {
            if(non_final_states.find(i) != non_final_states.end()){
                non_final_states.erase(i);
            }
            if (final_states.find(i) != final_states.end()){
                final_states.erase(i);
            }
        }
    }

    vector<set<int>> setOSt = { non_final_states, final_states};

    vector<set<int>> equivalence = equivalencetheorem(setOSt, transitionMap);

    int **transitionMap2 = (int**)malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++){
        transitionMap2[i] = (int*) malloc(26*sizeof(int));
        for (int j = 0; j < 26; j++){
            transitionMap2[i][j] = -1;
        }
    }
    int numtr = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 26; j++){
            if(transitionMap[i][j] != -1){
                int from;
                int to;
                for(int l = 0; l < equivalence.size(); l++){
                    if(equivalence[l].find(i) != equivalence[l].end()){
                        from = l;
                    }
                    if(equivalence[l].find(transitionMap[i][j]) != equivalence[l].end()){
                        to = l;
                    }
                }
                if(transitionMap2[from][j] != to){
                    transitionMap2[from][j] = to;
                    numtr++;
                }

            }
        }
    }

    set<int> minimized_final_states;

    for(auto it= final_states.begin(); it != final_states.end(); it++){
        for(int i = 0; i < equivalence.size(); i++){
            if(equivalence[i].find(*it) != equivalence[i].end()){
                minimized_final_states.insert(i);
            }
        }
    }

    cout << equivalence.size() <<  " " << numtr << " " << minimized_final_states.size() << endl;

    for(auto it = minimized_final_states.begin(); it != minimized_final_states.end(); it++){
        cout << *it << " ";
    }
    cout << endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 26; j++){
            if(transitionMap2[i][j] != -1){
                cout << i << " " << (char)(j+'a') << " " << transitionMap2[i][j] << endl;
            }
        }
    }




}