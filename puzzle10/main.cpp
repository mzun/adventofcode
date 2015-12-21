#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <utility>
#include <climits>

using std::cout; using std::cin;
using std::endl; using std::make_pair;
using std::pair;
using std::list; using std::string;
using std::map; using std::vector;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


class LookAndSay{
public:
    LookAndSay(string data){
        seed = data;
    };

    int run(int iterations)
    {
        string result = seed;
        for(int i = 0; i < iterations; ++i)
        {
            result = lookandsay(result);
        }
        return result.size();
    }

    string run2(int iterations)
    {
        return "";
    }


    string lookandsay(string in)
    {
        string result = "";
        int curr_cnt = 1;
        for (long i = 0; i < in.size(); ++i)
        {
            if ((i + 1) < in.size() && in[i+1] == in[i])
            {
                curr_cnt++;
            }
            else
            {
                result+=patch::to_string(curr_cnt);
                result+=in[i];
                curr_cnt = 1;
            }
        }
        return result;
    }


private:
    string seed;
    string data;
};


int main()
{
    LookAndSay lookAndSay("1321131112");

    cout << "Result: " << lookAndSay.run(50) << endl;

    return 0;
}
