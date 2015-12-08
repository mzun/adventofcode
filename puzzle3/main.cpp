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

using namespace std;

list<std::string> readInput_by_line(std::string file_name)
{
    list<std::string> data;
    fstream file;
    file.open(file_name.c_str());
    if (file.is_open())
    {
        std::string line;
        while(std::getline(file,line))
        {
            data.push_back(line);
        }
        file.close();
    }
    return data;
};

list<char> readInput_by_char(std::string file_name)
{
    list<char> data;
    fstream file;
    file.open(file_name.c_str());
    if (file.is_open())
    {
        char byte;
        while(file.get(byte))
        {
            data.push_back(byte);
        }
        file.close();
    }
    return data;
};

void move_santa (const char& dir, int& x, int& y)
{
    switch (dir)
    {
    case '<':
        --x;
        break;
    case '>':
        ++x;
        break;
    case '^':
        ++y;
        break;
    case 'v':
        --y;
        break;
    default:
        cout << "DUUUUUUUPA" << endl;
    }
}

void update_home_map(map<pair<int,int>, int>& hood, int x, int y)
{
    if (hood.find(make_pair(x,y)) == hood.end())
    {
        hood[make_pair(x,y)] = 1;
    }
    else
    {
        hood[make_pair(x,y)] +=1;
    }
}

void printMap(map<pair<int,int>, int> hood)
{
    list<int> x;
    list<int> y;
    for (map<pair<int,int>, int>::iterator it = hood.begin(); it != hood.end(); ++it)
    {
        x.push_back(it->first.first);
        y.push_back(it->first.second);
    }
    x.sort();
    y.sort();

    int xmin = *x.begin();
    int xmax = *x.rbegin();

    int ymin = *x.begin();
    int ymax = *x.rbegin();

    cout << endl << string((xmax - xmin + 1)*3 + 5, '*') << endl;
    for (int yy = ymax; yy>=ymin; --yy)
    {
        printf("%*d*",3,yy);
        for (int xx = xmin; xx<=xmax; ++xx)
        {
            if (hood.find(make_pair(xx,yy)) == hood.end())
            {
                cout << "   ";
            }
            else
            {
                printf("%*d",3, hood[make_pair(xx,yy)]);
            }
        }
        printf("*\n");
    }
    cout << string((xmax - xmin + 1)*3 + 5, '*') << endl;


}

int getHomeCount(list<char> data)
{
    map<pair<int,int>, int> result;

    int xSanta = 0,ySanta = 0;
    int xRoboSanta = 0,yRoboSanta = 0;
    result[make_pair(0,0)] =2;
    for(list<char>::iterator it = data.begin(); it!=data.end(); ++it){

        move_santa(*it,xSanta,ySanta);
        result[make_pair(xSanta,ySanta)] +=1;

        ++it; if (it == data.end()) break;

        move_santa(*it,xRoboSanta,yRoboSanta);
        result[make_pair(xRoboSanta,yRoboSanta)] +=1;
    }

    printMap(result);

    return result.size();
}


int main()
{
    list<char> data = readInput_by_char("input");
    int cnt = getHomeCount(data);

    cout << "input size: " << data.size() << endl;
    cout << "home count: " << cnt << endl;


    return 0;
}
