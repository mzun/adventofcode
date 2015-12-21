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
#include <utility>
#include <climits>

using std::cout; using std::cin;
using std::endl; using std::make_pair;
using std::pair;
using std::list; using std::string;
using std::map; using std::vector;


class Interpreter{
public:
    Interpreter(string name){
        readInput_by_line(name);
        parseData();
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

    static bool lt (int a, int b)
    {
        return a < b;
    }

    static bool gt (int a, int b)
    {
        return a > b;
    }

    int run()
    {
        list<string> tmp;
        return search_path(tmp,lt);
    }

    int run2()
    {
        list<string> tmp;
        return search_path(tmp,gt);
    }

    int getPathDistance(list<string> result)
    {
        int dist = 0;
        auto it = result.begin();
        auto it2 = result.begin(); it2++;

        while (it2 != result.end())
        {
            int tmpdist = getDistance(*it, *it2);
            if(tmpdist != -1)
            {
                dist+=tmpdist;
                ++it; ++it2;
            }
            else
            {
                return -1;
            }
        }

        return dist;
    }


private:

    list<string> data;
    map<pair<string,string>,int> distances;
    list<string> towns;

    // towns must exist!!!
    int getMinDistance()
    {
        int best_result = -1;


        return best_result;
    }

    int search_path(list<string> result, bool (*compare)(int,int))
    {
        static int best_result = -1;
        static list<string> best_path;
        static int cnt = 0;

        if (result.size() == towns.size())
        {
            int tmp_result = getPathDistance(result);

            //cout << "Check best result: " << tmp_result << endl;

            if ((*compare)(tmp_result, best_result) || best_result == -1)
            {
                cout << "New best result: " << best_result << endl;
                for (auto &s : result)
                {
                    cout << s << " -> ";
                }
                cout << endl;
                best_result = tmp_result;
                best_path = result;
            }

        }
        else
        {
            //cout << "Go into " << endl;
            for (auto next_town : towns)
            {
                if (std::find(result.begin(), result.end(), next_town) == result.end())
                {
                    list<string> tmp_result = result;
                    tmp_result.push_back(next_town);
                    search_path(tmp_result, compare);
                }
            }
        }
        if(!cnt++)
        {
            cout << "Parsed: " << cnt << endl;
        }
        return best_result;
    }

    void parseData()
    {
        for (auto &s:data)
        {
            vector<string> tokens = split(s," ");

            if (tokens.size() == 5)
            {
                ins(tokens[0],tokens[2],tokens[4]);
            }

        }
    }

    void ins(string town1, string town2, string distance)
    {
        //cout << "Try to insert: " << town1 << " and " << town2 << " : " << distance << endl;
        if (getDistance(town1, town2) < 0 )
        {
            int conv_distance = atoi(distance.c_str());
            distances[make_pair(town1,town2)] = conv_distance;
            //cout << "Inserted value: " << conv_distance << endl;
        }
        if (std::find(towns.begin(), towns.end(), town1) == towns.end())
        {
            //cout << "Inserted town: " << town1 << endl;
            towns.push_back(town1);
        }
        if (std::find(towns.begin(), towns.end(), town2) == towns.end())
        {
            //cout << "Inserted town: " << town2 << endl;
            towns.push_back(town2);
        }
    }

    int getDistance(string town1, string town2)
    {
        int distance = -1;
        if (distances.find(make_pair(town1,town2)) != distances.end())
        {
            distance = distances[make_pair(town1,town2)];
        }
        else if (distances.find(make_pair(town2,town1)) != distances.end())
        {
            distance = distances[make_pair(town2,town1)];
        }

        //cout << "Retrieved distance from " << town1 << " to " << town2 << " :" << distance << endl;

        return distance;
    }


    vector<string> split(const string str, const string delim)
    {
        vector<string> v ; //Use vector to add the words
        size_t prev_pos = 0, pos;
        while ((pos = str.find_first_of(delim, prev_pos)) != std::string::npos)
        {
            if (pos > prev_pos)
                v.push_back(str.substr(prev_pos, pos-prev_pos));
            prev_pos= pos+1;
        }
        if (prev_pos< str.length())
            v.push_back(str.substr(prev_pos, std::string::npos));

        return v;
    }

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
    Interpreter interpreter("input");
    interpreter.printData();

    cout << "Result: " << interpreter.run() << endl;
    cout << "Result2: " << interpreter.run2() << endl;

    return 0;
}
