#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>

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

list<unsigned char> readInput_by_char(std::string file_name)
{
    list<unsigned char> data;
    fstream file;
    file.open(file_name.c_str());
    if (file.is_open())
    {
        char byte;
        while(file.get(byte))
        {
            data.push_back(static_cast<unsigned char>(byte));
        }
        file.close();
    }
    return data;
};

class Box{
public:
     Box() : l(0), w(0), h(0) {}
     Box(int _l, int _w, int _h) : l(_l), w(_w), h(_h) {}

    int getArea() {
        return getBoxArea() + getAdditionalSlack();
    }

    int getRibbonLength(){
        int tab[3] = {l,w,h};
        sort(tab,tab+3);

        return 2*tab[0]+2*tab[1]+l*w*h;
    }
private:
    int l;
    int w;
    int h;

    int getBoxArea() {
        return 2*l*w + 2*w*h + 2*l*h;
    }

    int getAdditionalSlack(){
        int tab[3] = {l,w,h};
        sort(tab,tab+3);
        return tab[0]*tab[1];
    }
};



list<Box> loadBoxes (list<std::string> data)
{
    list<Box> result;

    for(list<std::string>::iterator it = data.begin(); it!= data.end(); ++it)
    {
        vector<int> vec;

        stringstream ss(*it);
        string val;
        while(getline(ss,val,'x')){
            vec.push_back(atoi(val.c_str()));
        }
        if (vec.size() == 3)
        {
            Box b(vec[0],vec[1],vec[2]);
            result.push_back(b);
        }
    }

    return result;
}

int main()
{
    list<std::string> data = readInput_by_line("input");

    list<Box> boxes = loadBoxes(data);

    int area = 0;
    int ribbon = 0;
    int cnt = 0;

    for (list<Box>::iterator it = boxes.begin(); it!=boxes.end(); ++it){
        ++cnt;
        area += it->getArea();
        ribbon += it->getRibbonLength();
    }

    //std::copy(data.begin(), data.end(), ostream_iterator<std::string>(cout, "\n"));

    cout << ribbon <<" Hello world! : " << area << endl;
    return 0;
}
