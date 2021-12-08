#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <tuple>

using namespace std;

// GLOBALS
vector<int> states;
vector<tuple<int, char, int>> trans;
int start, accept;

int prec(char c)
{
    switch (c)
    {
    case '*':
        return 3;
    case '.':
        return 2;
    case '+':
        return 1;
    case '(':
        return 0;
    default:
        return -1;
    }
}

string toPoFix(string reg)
{
    stack<char> st;
    string poFix;
    set<char> op = {'*', '.', '+', '(', ')'};
    for (char &c : reg)
    {
        if (op.find(c) != op.end())
        {
            if (c == '(')
            {
                st.push(c);
            }
            else if (c == ')')
            {
                while (st.top() != '(')
                {
                    poFix += st.top();
                    st.pop();
                }
                st.pop();
            }
            else
            {
                while (!st.empty() && prec(c) <= prec(st.top()))
                {
                    poFix += st.top();
                    st.pop();
                }
                st.push(c);
            }
        }
        else
        {
            poFix += c;
        }
    }
    while (!st.empty())
    {
        poFix += st.top();
        st.pop();
    }

    return poFix;
}

void NFA(string poFix)
{
    stack<pair<int, int>> st;
    start = 0;
    accept = 1;
    int i = 0;
    for (char &c : poFix)
    {
        if (c >= 'a' && c <= 'z')
        {
            st.push(make_pair(i, i + 1));
            states.push_back(i);
            states.push_back(i + 1);
            trans.push_back(make_tuple(i, c, i + 1));
            i += 2;
        }
        else if (c == '.')
        {
            auto s1 = st.top();
            st.pop();
            auto s2 = st.top();
            st.pop();
            st.push(make_pair(s2.first, s1.second));
            trans.push_back(make_tuple(s2.second, 'E', s1.first));
            if (s2.second == accept)
                accept = s1.second;
        }
        else if (c == '+')
        {
            auto s1 = st.top();
            st.pop();
            auto s2 = st.top();
            st.pop();
            st.push(make_pair(i, i + 1));
            states.push_back(i);
            states.push_back(i + 1);
            trans.push_back(make_tuple(i, 'E', s1.first));
            trans.push_back(make_tuple(i, 'E', s2.first));
            trans.push_back(make_tuple(s1.second, 'E', i + 1));
            trans.push_back(make_tuple(s2.second, 'E', i + 1));
            if (s1.first == start || s2.first == start)
                start = i;
            if (s1.second == accept || s2.second == accept)
                accept = i + 1;
            i += 2;
        }
        else if (c == '*')
        {
            auto s1 = st.top();
            st.pop();
            st.push(make_pair(i, i));
            states.push_back(i);
            trans.push_back(make_tuple(i, 'E', s1.first));
            trans.push_back(make_tuple(s1.second, 'E', i));
            if (s1.first == start)
                start = i;
            if (s1.second == accept)
                accept = i;
            i++;
        }
    }
}

void swapStart()
{
    int st = start;
    if (st == 0)
        return;
    start = 0;
    for (auto &t : trans)
    {
        if (get<0>(t) == st)
            get<0>(t) = 0;
        else if (get<0>(t) == 0)
            get<0>(t) = st;

        if (get<2>(t) == st)
            get<2>(t) = 0;
        else if (get<2>(t) == 0)
            get<2>(t) = st;
    }
}

void solve()
{
    string s;
    cin >> s;
    string cstr = "";
    for (int i = 0; i < s.size(); i++)
    {
        cstr += s[i];
        if (s[i] == ')' || s[i] == '*' || (s[i] >= 'a' && s[i]))
        {
            if (s[i + 1] == '(' || (s[i + 1] >= 'a' && s[i + 1] <= 'z'))
            {
                cstr += '.';
            }
        }
    }
    string poFix = toPoFix(cstr);
    NFA(poFix);
    swapStart();
    cout << states.size() << " " << trans.size() << " 1" << endl;
    cout << accept << endl;
    for (auto &i:trans)
    {
        cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    solve();
    return 0;
}