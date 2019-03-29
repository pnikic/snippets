#include <cctype>
#include <cstdio>

inline int get()
{
#ifdef _WIN32
    return _getchar_nolock();
#else
    return getchar_unlocked();
#endif
}

int read()
{
    int ret = 0, chr = get();
    while (isspace(chr)) chr = get();
    while (isdigit(chr)) ret = 10 * ret + chr - '0', chr = get();
    return ret;
}
