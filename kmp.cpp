#include <string>
#include <vector>
using namespace std;

typedef vector<int> vi;

void init(string& P, vi& b)
{
    int i = 0, j = -1; b[0] = -1;
    while (i < P.size())
    {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        b[++i] = ++j;
    }
}

vi kmp(string& T, string& P, vi& b)
{
    vi ret;
    int i = 0, j = 0;
    while (i < T.size())
    {
        while (j >= 0 && T[i] != P[j]) j = b[j];
        ++i; ++j;
        if (j == P.size())
        {
            ret.push_back(i - j);
            j = b[j];
        }
    }
    return ret;
}
