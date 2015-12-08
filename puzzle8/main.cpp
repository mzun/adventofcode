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
#include <cctype>

using std::cout; using std::cin;
using std::endl;
using std::list; using std::string;
using std::map; using std::vector;

class AnotherCounter{
public:
    AnotherCounter(string name){
        readInput_by_line(name);
    };


    list<string>& getData()
    {
        return data;
    }

    void printData(){
        for (auto& s : data)
        {
            cout << s << endl;
        }
        cout << endl;
    }

    int run()
    {
        int all = 0;
        int printed = 0;
        for(auto&s : data)
        {
            all += s.length();
            printed += parseString(s);

            cout << s << " | printed: " << parseString(s) << " len: " << s.length() << endl;
        }

        return all - printed;
    }

    string encodeString(string s)
    {

    }

    int parseString(string s)
    {
        int printed = 0;
        for(int i = 0; i < s.length(); i++)
        {
            if (s[i] == '\\')
            {
                if((i + 1) < s.length() && (s[i+1] == '\\' || s[i+1] == '\"'))
                {
                    ++i;
                }
                else if ((i + 3) < s.length() && s[i+1] == 'x')
                {
                    i += 3;
                }
                ++printed;
            }
            else if (s[i] == '\"')
            {

            }
            else
            {
                ++printed;
            }
        }
        return printed;
    }

private:

    list<string> data;

    void readInput_by_line(string file_name)
    {
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
    };
};



int main()
{
    AnotherCounter counter("input");
    //counter.printData();
    //string s = "\"\\x27\"";
    //cout << s <<" result: " << counter.parseString(s) << " length: " << s.length() << endl;

    cout << "Result: " << counter.run() << endl;

    return 0;
}
