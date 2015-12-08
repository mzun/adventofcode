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

using std::cout; using std::endl;
using std::list; using std::string;
using std::map;

list<string> readInput_by_line(string file_name)
{
    list<string> data;
    std::fstream file;
    file.open(file_name.c_str());
    if (file.is_open())
    {
        string line;
        while(std::getline(file,line))
        {
            data.push_back(line);
        }
        file.close();
    }
    return data;
};

bool checkVowelReq(char letter)
{
    static char vowels[] = "aeiou";
    for (int i = 0; i < 5; ++i)
    {
        if (vowels[i] == letter)
        {
            return true;
        }
    }
    return false;

}

bool checkIfBadColloc(char letter, char followingLetter, map<char,char>& badColloc)
{
    bool res = false;
    if (badColloc.find(letter) != badColloc.end() && badColloc[letter] == followingLetter)
    {
        res = true;
    }
    return res;
}

bool checkIfStringIsNice(string s)
{
    int vowel_cnt = 0;
    static const int vowel_req_min = 3;

    int double_cnt = 0;
    static const int double_req_min = 1;

    map<char,char> badCollocMap;
    badCollocMap['a'] = 'b';
    badCollocMap['c'] = 'd';
    badCollocMap['p'] = 'q';
    badCollocMap['x'] = 'y';

    int bad_coloc_cnt = 0;
    int bad_colloc_req_max = 0;

    for(int i = 0; i < s.length() ; i++)
    {
        if (checkVowelReq(s[i]))
        {
            ++vowel_cnt;
        }
        if ((i+1) < s.length())
        {
            if (s[i] == s[i+1])
            {
                ++double_cnt;
            }
            if (checkIfBadColloc(s[i], s[i+1], badCollocMap))
            {
                ++bad_coloc_cnt;
            }
        }
    }

    //cout << s <<"| Vowels: " << vowel_cnt << ", Doubles: " << double_cnt << ", Bad_collocs: " << bad_coloc_cnt << endl;

    if (vowel_cnt >= vowel_req_min && double_cnt >= double_req_min && bad_coloc_cnt <= bad_colloc_req_max )
        return true;
    else
        return false;
}

bool checkIfOccurAgain(string seed, string checked)
{
    //cout << "Seed: " << seed << ", checked: " << checked << endl;
    size_t found = checked.find(seed);
    if (found != std::string::npos)
            return true;
    return false;
}

bool checkIfStringIsNice2(string s)
{
    int double_cnt = 0;
    static const int double_req_min = 1;

    int repeat_cnt = 0;
    static const int repeat_req_min = 1;

    for(int i = 0; i < s.length() ; i++)
    {
        if(i<s.length()-2)
        {
            if (checkIfOccurAgain(s.substr(i,2), s.substr(i+2)))
            {
                ++double_cnt;
                //cout << "Double occured: " << double_cnt << endl;
            }
            if (s[i] == s[i+2])
            {
                ++repeat_cnt;
            }
        }

    }
    if (double_cnt >= double_req_min && repeat_cnt >= repeat_req_min )
        return true;
    else
        return false;
}

int main(int argc, char *argv[])
{
    list<string> data = readInput_by_line("input");

    int cnt = 0;
    int cnt2 = 0;
    for(list<string>::iterator it = data.begin(); it!=data.end(); ++it)
    {
        if(checkIfStringIsNice(*it))
            ++cnt;
        if(checkIfStringIsNice2(*it))
            ++cnt2;
    }

    cout << "Cnt = " << cnt << ", Cnt2 = " << cnt2 << endl;

    return 0;
}
