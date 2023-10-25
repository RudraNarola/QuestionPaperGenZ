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

class QuestionPaper
{
private:
    int noOfEasy = 0, noOfHard = 0, noOfMedium = 0, copies = 0, totalEasy = 0, totalMed = 0, totalHard = 0;
    int totalQuestions = 0;
    vector<string> easy, medium, hard;
    vector<int> shuffEasy, shuffMed, shuffHard;
    vector<vector<int>> que;

public:
    QuestionPaper(int easy, int medium, int hard, int copies)
    {
        this->noOfEasy = easy;
        this->noOfMedium = medium;
        this->noOfHard = hard;
        this->copies = copies;
        this->totalQuestions = easy + medium + hard;
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
                if (mychar == '\n')
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

        this->totalEasy = easy.size();
        this->totalMed = medium.size();
        this->totalHard = hard.size();

        shuffEasy.resize(totalEasy);
        shuffMed.resize(totalMed);
        shuffHard.resize(totalHard);

        for (int i = 0; i < totalEasy; i++)
            shuffEasy[i] = i;
        for (int i = 0; i < totalMed; i++)
            shuffMed[i] = i;
        for (int i = 0; i < totalHard; i++)
            shuffHard[i] = i;

        random_device e1; // shuffling index for question to make random selection among multiple paper distributive
        mt19937 g1(e1());
        shuffle(shuffEasy.begin(), shuffEasy.end(), g1);

        random_device e2;
        mt19937 g2(e2());
        shuffle(shuffMed.begin(), shuffMed.end(), g2);

        random_device e3;
        mt19937 g3(e3());
        shuffle(shuffHard.begin(), shuffHard.end(), g3);

        debug(shuffEasy, shuffHard, shuffMed);
        // storing the needed quantity of questions in a vector

        for (int i = 0; i < copies; i++)
        {
            vector<int> temp;
            for (int e = 0; e < noOfEasy; e++)
            {
                temp.push_back(shuffEasy[e]);
            }
            for (int m = 0; m < noOfMedium; m++)
            {
                temp.push_back(shuffMed[m]);
            }
            for (int h = 0; h < noOfHard; h++)
            {
                temp.push_back(shuffHard[h]);
            }

            que.push_back(temp);
        }
        debug(que);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("d.txt", "w", stderr);
#endif
    int noOfEasy = 0, noOfMedium = 0, noOfHard = 0, copies = 0;
    printf("Enter the number of easy questions: ");
    cin >> noOfEasy;
    printf("Enter the number of medium questions: ");
    cin >> noOfMedium;
    printf("Enter the number of hard questions: ");
    cin >> noOfHard;
    printf("Number of papers you want: ");
    cin >> copies;
    auto q = QuestionPaper(noOfEasy, noOfMedium, noOfHard, copies);
    q.createPaper();
}