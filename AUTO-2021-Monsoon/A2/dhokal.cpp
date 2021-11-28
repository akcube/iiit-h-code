#include<iostream>
#include<bits/stdc++.h>
using namespace std;
bool stateinvector(vector<int> states,int state_c);
bool alphainvector(vector<char> alpha,int alphabet_c);

int precedence(char c)
{
    if(c=='*')
        return 3;
    else if(c=='.')
        return 2;
    else if(c=='+')
        return 1;
    else if(c=='(')
        return 0;
    else
        return -1;
}

typedef struct transition
{
    int curr;
    char c;
    int next;
}transition;



string Topostfix(string regex)
{
    stack<char> op_stack;
    string postfix;
    for(int i=0;i<regex.length();i++)
    {
        if(regex[i] == '*' || regex[i] == '.' || regex[i] == '+' || regex[i] == '(' || regex[i] == ')')
        {
            if(regex[i] == '(')
            {
                op_stack.push(regex[i]);
            }
            else if(regex[i] == ')')
            {
                while(op_stack.top() != '(')
                {
                    postfix.push_back(op_stack.top());
                    op_stack.pop();
                }
                op_stack.pop();
            }
            else
            {
                while(!op_stack.empty() && precedence(op_stack.top()) >= precedence(regex[i]))
                {
                    postfix.push_back(op_stack.top());
                    op_stack.pop();
                }
                op_stack.push(regex[i]);
            }
        }
        else
        {
            postfix.push_back(regex[i]);
        }
    }
    while(!op_stack.empty())
    {
        postfix.push_back(op_stack.top());
        op_stack.pop();
    }

    return postfix;

}
typedef struct NFA
{
    vector<int> states;
    vector<char> alphabet;
    vector<transition> trans;
    vector<int> start_state,final_state;


} NFA;

void addstate(vector<int> &states, int state_c)
{
    if (!stateinvector(states,state_c))
    {
        states.push_back(state_c);
    }


}

void addalphabet(vector<char> &alphabet, char c)
{
    if(!alphainvector(alphabet,c))
    {
        alphabet.push_back(c);
    }
}
bool stateinvector(vector<int> states,int state_c)
{
    for(int i = 0;i<states.size();i++)
    {
        if (states[i] == state_c){
            return 1;
        }
    }
    return 0;
}
bool alphainvector(vector<char> alpha,int alphabet_c)
{
    for(int i = 0;i<alpha.size();i++)
    {
        if (alpha[i] == alphabet_c){
            return 1;
        }
    }
    return 0;
}


NFA regextoNFA(string regex)
{
    stack<NFA> nfa;
    int state_count = 0;

    for (int i = 0; i < regex.length() ; i++)
    {
        if(regex[i] <= 'z' && regex[i] >= 'a')
        {
            NFA n;
            int from = state_count;
            int to = state_count+1;
            if (stateinvector(n.states,from) == 0)
            {
                n.states.push_back(from);
            }
            if (stateinvector(n.states,to) == 0)
            {
                n.states.push_back(to);
            }
            n.trans.push_back({from,regex[i],to});
            if (alphainvector(n.alphabet,regex[i]))
            {
                n.alphabet.push_back(regex[i]);
            }
            if(stateinvector(n.start_state,from) == 0)
            {
                n.start_state.push_back(from);
            }
            if(stateinvector(n.final_state,to) == 0)
            {
                n.final_state.push_back(to);
            }
            nfa.push(n);
            state_count+=2;
        }
        else if (regex[i] == '*')
        {
            NFA n = nfa.top();
            nfa.pop();
            NFA n1;
            addstate(n1.start_state,state_count);
            for (int j = 0; j < n.states.size(); j++)
            {
                addstate(n.states,n.states[j]);
            }
            addstate(n1.states,state_count);
            for (int j = 0; j < n.final_state.size(); j++)
            {
                addstate(n1.final_state,n.final_state[j]);
            }
            addstate(n1.final_state,state_count);
            for (int j = 0; j < n.alphabet.size(); j++)
            {
                addalphabet(n1.alphabet,n.alphabet[j]);
            }
            for (int j = 0; j < n.trans.size(); j++)
            {
                n1.trans.push_back(n.trans[j]);
            }

            n1.trans.push_back({state_count,'_',n.start_state[0]});

            for (int j = 0; j < n.final_state.size(); j++)
            {
                transition temp = {n.final_state[j],'_',n.start_state[0]};
                n1.trans.push_back(temp);
            }
            nfa.push(n1);
            state_count+=1;
        }
        else if (regex[i]== '.')
        {
            NFA n1 = nfa.top();
            nfa.pop();
            NFA n2 = nfa.top();
            nfa.pop();
            NFA n;
            for (int j = 0; j< n1.states.size(); j++)
            {
                addstate(n.states,n1.states[j]);
            }
            for (int j = 0; j < n2.states.size(); j++)
            {
                addstate(n.states,n2.states[j]);
            }
            for (int j = 0; j < n1.alphabet.size(); j++)
            {
                addalphabet(n.alphabet,n1.alphabet[j]);
            }
            for (int j = 0; j < n2.alphabet.size(); j++)
            {
                addalphabet(n.alphabet,n2.alphabet[j]);
            }
            for (int j = 0; j < n1.trans.size(); j++)
            {
                n.trans.push_back(n1.trans[j]);
            }
            for (int j = 0; j < n2.trans.size(); j++)
            {
                n.trans.push_back(n2.trans[j]);
            }

            for (int j = 0; j < n2.start_state.size(); j++)
            {
                addstate(n.start_state,n2.start_state[j]);
            }
            for (int j = 0; j < n1.final_state.size(); j++)
            {
                addstate(n.final_state,n1.final_state[j]);
            }
            for(int j = 0; j < n2.final_state.size(); j++)
            {
                transition temp = {n2.final_state[j],'_',n1.start_state[0]};
                n.trans.push_back(temp);
            }
            nfa.push(n);
        }
        else if (regex[i]=='+')
        {
            NFA n1 = nfa.top();
            nfa.pop();
            NFA n2 = nfa.top();
            nfa.top();
            NFA n;
            addstate(n.start_state,state_count);
            addstate(n.states,state_count);
            for (int j = 0; j < n1.states.size(); j++)
            {
                addstate(n.states,n1.states[j]);
            }
            for (int j = 0; j < n2.states.size(); j++)
            {
                addstate(n.states,n2.states[j]);
            }
            for (int j = 0; j < n1.alphabet.size(); j++)
            {
                addalphabet(n.alphabet,n1.alphabet[j]);
            }
            for (int j = 0; j < n2.alphabet.size(); j++)
            {
                addalphabet(n.alphabet,n2.alphabet[j]);
            }
             for (int j = 0; j < n1.trans.size(); j++)
            {
                n.trans.push_back(n1.trans[j]);
            }
            for (int j = 0; j < n2.trans.size(); j++)
            {
                n.trans.push_back(n2.trans[j]);
            }
            for (int j=0; j< n1.final_state.size();j++)
            {
                addstate(n.final_state,n1.final_state[j]);
            }
            for(int j=0; j< n2.final_state.size();j++)
            {
                addstate(n.final_state,n2.final_state[j]);
            }
            for (int j = 0; j < n1.start_state.size(); j++)
            {
                transition temp = {state_count,'_',n1.start_state[j]};
                n.trans.push_back(temp);
            }
            for(int j =0; j< n2.start_state.size();j++)
            {
                transition temp = {state_count, '_',n2.start_state[j]};
                n.trans.push_back(temp);
            }

            state_count+=1;
            nfa.push(n);
        }



    }
    return nfa.top();
}


int main()
{
    stack<string> regex;
    string str;
    cin>>str;
    int n=str.length();

    // adding concat symbol for future
    string cstr = "";
    for (int i = 0; i < n; i++)
    {
        cstr+=str[i];
        if (str[i] == ')' || str[i] == '*' || (str[i] >= 'a' && str [i] ))
        {
            if (str[i+1] == '(' || (str[i+1] >= 'a' && str [i+1] <= 'z' ) ){
                cstr+='.';
            }
        }
    }

   cout<<cstr<<endl;

    cstr = Topostfix(cstr);
    cout<<cstr<<endl;

    NFA nfa = regextoNFA(cstr);
    cout<<"States: ";
    for (int i = 0; i < nfa.states.size(); i++)
    {
        cout<<nfa.states[i]<<" ";
    }
    cout<<endl;
    cout<<"Alphabet: ";
    for (int i = 0; i < nfa.alphabet.size(); i++)
    {
        cout<<nfa.alphabet[i]<<" ";
    }
    cout<<endl;
    cout<<"Start : ";
    for (int i = 0; i < nfa.start_state.size(); i++)
    {
        cout<<nfa.start_state[i]<<" ";
    }
    cout<<endl;
    cout<<"Final: ";
    for (int i = 0; i < nfa.final_state.size(); i++)
    {
        cout<<nfa.final_state[i]<<" ";
    }
    cout<<endl;
    cout<<"Transitions: ";
    for(int i=0;i<nfa.trans.size();i++)
    {
        cout << nfa.trans[i].curr << " " << nfa.trans[i].c << " " << nfa.trans[i].next;
        cout << endl;
    }

}