#include <bits/stdc++.h>
using namespace std;

void __print(int x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif

///
///
///
///
///

class QuestionPaper
{
    int noOfEasy = 0, noOfHard = 0, noOfMedium = 0;
    vector<string> easy, medium, hard;

    QuestionPaper(int easy, int medium, int hard)
    {
        this->noOfEasy = easy;
        this->noOfMedium = medium;
        this->noOfHard = hard;
    }

    void readFile(vector<string> &que, string s)
    {
        string temp = "";
        string path = s + ".txt";
        ifstream myfile(path);
        if (myfile.is_open())
        {
            char mychar;
            while (myfile)
            {
                mychar = myfile.get();
                if (mychar == '@')
                {
                    que.push_back(temp);
                    temp.clear();
                }
                else
                    temp += mychar;
            }
        }
    }

    void createPaper()
    {
        if (noOfEasy)
            readFile(easy, "EASY");
        if (noOfMedium)
            readFile(medium, "MEDIUM");
        if (noOfHard)
            readFile(hard, "HARD");
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("t.txt", "w", stderr);
#endif
    int noOfEasy = 0, noOfMedium = 0, noOfHard = 0;
    printf("Enter the number of easy questions: ");
    cin >> noOfEasy;
    printf("Enter the number of medium questions: ");
    cin >> noOfMedium;
    printf("Enter the number of hard questions: ");
    cin >> noOfHard;
    
}