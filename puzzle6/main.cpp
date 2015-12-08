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

using std::cout; using std::cin;
using std::endl;
using std::list; using std::string;
using std::map; using std::vector;

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

class Grid{
public:
    Grid (int _a) : a(_a)
    {
        data = new int*[a];
        for(int i = 0;  i < a; ++i)
        {
            data[i] = new int[a];
        }
    }

    ~Grid() {
        for (int i = 0; i < a; ++i)
        {
            delete [] data[i];
        }
        delete [] data;
    }


    static void turn_on (int&a)
    {
        a += 1;
    }

    static void turn_off (int &a)
    {
        a -= 1;
        if (a < 0)
            a = 0;
    }

    static void toggle (int &a)
    {
        a +=2;
    }

    static void count_lights(int&a)
    {
        lights_on+=a;
    }

    void modify (int xs, int ys, int xf, int yf, void (*sth)(int&d))
    {
        for (int yy = ys; yy <= yf; ++yy)
        {
            for (int xx = xs; xx <= xf; ++xx)
            {
                //data[xx][yy] = 1;
                (*sth)(data[xx][yy]);
            }
        }
    }

    void print(){

        cout << endl << string((a + 1)*3 + 3, '*') << endl;
        for (int yy = a-1; yy >= 0; --yy)
        {
            printf("%*d*",3,yy);
            for (int xx = 0; xx < a; ++xx)
            {
                printf("%*d",3, data[xx][yy]);
            }
            printf(" *\n");
        }
        cout << string((a + 1)*3 + 3, '*') << endl;
    }

    int getOnLightsCnt()
    {
        lights_on = 0;
        modify(0,0,a-1,a-1,count_lights);
        return lights_on;
    }


private:
    int a;
    int **data;

    static int lights_on;
};

int Grid::lights_on = 0;


vector<string> split(const string str, const string delim) {

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

void followInstructions(Grid& grid, list<string>& instr)
{
    for(list<string>::iterator it = instr.begin(); it != instr.end(); ++it)
    {
        vector<string> current_instruction;
        current_instruction = split(*it, " ,");

        //cout << *it << "|";
        if (current_instruction.size() == 7)
        {
            int xs = atoi(current_instruction[2].c_str());
            int ys = atoi(current_instruction[3].c_str());
            int xf = atoi(current_instruction[5].c_str());
            int yf = atoi(current_instruction[6].c_str());

            if (current_instruction[1] == "on")
            {
                grid.modify(xs,ys,xf,yf,Grid::turn_on);
            }
            else if (current_instruction[1] == "off")
            {
                grid.modify(xs,ys,xf,yf,Grid::turn_off);
            }

        }
        else if (current_instruction.size() == 6)
        {
            int xs = atoi(current_instruction[1].c_str());
            int ys = atoi(current_instruction[2].c_str());
            int xf = atoi(current_instruction[4].c_str());
            int yf = atoi(current_instruction[5].c_str());
            grid.modify(xs,ys,xf,yf,Grid::toggle);
        }
        cout << endl;
    }
}

int main()
{
    Grid grid(1000);
    list<string> instr = readInput_by_line("input");

    followInstructions(grid,instr);

    grid.print();

    cout << "Lights: " << grid.getOnLightsCnt() << endl;

    return 0;
}
