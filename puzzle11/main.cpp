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

class PasswordUpdater
{
public:

    string getNextPassword(string seed)
    {
        bool found = false;
        string next_password = seed;
        int cnt = 0;
        while(!found)
        {
            next_password = increment_string(next_password);
            bool f1 = check_tuples(next_password,2);
            bool f2 = !check_forbidden_letters(next_password,"iol");
            bool f3 = check_increasing_straight(next_password);

            //cout << cnt++ << " Password: " << next_password << " tuples: " << f1 << ", not forbidden: " << f2 << ", straight: " << f3 << endl;

            if(f1 && f2 && f3)
            {
                break;
            }
        }
        return next_password;
    }


private:



    bool check_tuples(string s, int treshold)
    {
        map<char,int> tuples;
        for(int i = 0; i < s.size(); ++i)
        {
            int j = 0;
            while((i+j+1) < s.size() && s[i+j+1] == s[i+j])
            {
                ++j;
                if(j >= (treshold-1))
                {
                    tuples[s[i+j]] = j+1;
                    //cout << "Letter: " << s[i+j] << " how many: " << j << endl;
                }
            }
            i+=j;
        }

        return tuples.size() > 1;
    }


    bool check_forbidden_letters(string s, string forbidden)
    {
        for(int i = 0; i< s.size(); ++i)
        {
            size_t found = forbidden.find(s[i]);
            //cout << s[i] << " ? contains forbidden " << forbidden << " : " << found << " == " << std::string::npos << endl;
            if (found != std::string::npos)
            {
                return true;
            }
        }
        return false;
    }

    bool check_increasing_straight(string s)
    {
        int cnt = 0;
        static int required_cnt = 2;
        bool ret = false;
        for(int i = 0; i < s.size(); ++i)
        {
            if((i+1) < s.size() && s[i+1] == (s[i]+1))
            {
                ++cnt;
            }
            else if (cnt == required_cnt)
            {
                ret = true;
                break;
            }
            else
            {
                cnt = 0;
            }
        }
        return ret;
    }

    string increment_string(string s)
    {
        for(int i = s.size() - 1; i>=0; --i )
        {
            s[i] = increment_letter(s[i]);
            if (s[i] != 'a')
            {
                break;
            }
        }
        return s;
    }


    char increment_letter (char letter)
    {
        char ret = std::tolower(letter);

        return (ret+1) > 'z' ? 'a' : (ret+1);
    }


};

int main()
{
    string seed = "vzbxkghb";
    PasswordUpdater updater;

    string sec = updater.getNextPassword(seed);
    string thr = updater.getNextPassword(sec);

    cout << "Pass 2: " << sec << endl;
    cout << "Pass 3: " << thr << endl;
    return 0;
}
