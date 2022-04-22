#include "LIST.H"
#include <iostream>


int main()
{
    for(int i = 0; i < 1000; ++i)
    {
        List<int> l;
        for(int i1 = 0; i1 < 2'000'000; ++i1)
        {
            l.push_back(i1);
        }
    }
    return 0;
}