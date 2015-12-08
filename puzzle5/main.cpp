#include <iostream>
#include "md5.h"
#include <cstdio>

using std::cout; using std::endl;

int getCipherCnt(int nb)
{
    int res = 0;
    while (nb%10 ||  nb)
    {
        ++res;
        nb/=10;
    }
    return res;
}

bool checkIfZerosString(const char* val, int len)
{
    for (int i = 0; i<len; ++i)
    {
        if (val[i] != '0')
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    long long i = 1;
    char seed[] = "yzbqklnj";
    char buff[400];
    bool found = false;
    while (!found)
    {
        sprintf(buff,"%s%d",seed,i);
        std::string result = md5(std::string(buff));

        if (checkIfZerosString(result.c_str(),5) || checkIfZerosString(result.c_str(),6))
        {
            if (checkIfZerosString(result.c_str(),6))
            {
                found = true;
            }
            cout << "buff " << buff << " || Result = " << i << " result hash = " << result << endl;
        }
        if (!(i%10000000))
        {
            cout << "Checked : " << i << endl;
        }
        ++i;
    }
  //  cout << "md5 of 'abcdef609043': " << md5("abcdef609043") << endl;
    return 0;
}
