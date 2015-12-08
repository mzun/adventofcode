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

class Interpreter{
public:
    Interpreter(string name){
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

    void run(){
        list<string> data =  this->data;
        if (data.size() > 0){
            int cnt = 0;
            while (state.find("a") == state.end() && data.size() > 0)
            {
                //cout << "Cnt: " << cnt << "  state.size = " << state.size()  << "  data.size = " << data.size() << endl;
                for(list<string>::iterator it = data.begin(); it!=data.end();)
                {
                    vector<string> order = split(*it, " ");
                    if (order.size() > 0)
                    {
                        bool valid = false;
                        uint16_t result_value = -1;
                        string result_key;

                        if (order[1] == "AND")
                        {
                            result_value = doLogicOperation(order[0],order[2],op_and,valid);
                            result_key = order[4];
                        }
                        else if (order[1] == "OR")
                        {
                            result_value = doLogicOperation(order[0],order[2],op_or,valid);
                            result_key = order[4];
                        }
                        else if (order[1] == "LSHIFT")
                        {
                            result_value = doLogicOperation(order[0],order[2],op_lshift,valid);
                            result_key = order[4];
                        }
                        else if (order[1] == "RSHIFT")
                        {
                            result_value = doLogicOperation(order[0],order[2],op_rshift,valid);
                            result_key = order[4];
                        }
                        else if (order[0] == "NOT")
                        {
                            result_value = doLogicOperation(order[1],"65535",op_xor,valid);
                            result_key = order[3];
                        }
                        else // number to be set
                        {
                            cout << "set op: "<< *it << endl;
                            result_value = doLogicOperation(order[0],"65535",op_set,valid);
                            result_key = order[2];
                            if (state.find(result_key) != state.end())
                                valid = false;
                            //getSubstrat(result_key,valid);
                        }

                        if(valid)
                        {
                            //cout << "valid op: "<< *it << " key: " << result_key << " value: " << result_value << endl;
                            state[result_key] = result_value;
                            remove_and_advance(it);
                            //cout << "---------------------------------------------------------"<< endl;
                        }
                        else
                        {
                            ++it;
                        }

                    }
                    else
                    {
                        remove_and_advance(it);
                    }

                }
                cout << "==========================================================================="<< endl;
                cout << "Cnt: " << ++cnt << "  state.size = " << state.size() << "  data.size = " << data.size() << endl;
                cout << "==========================================================================="<< endl;
            }
        }
        else{
            cout << "Bad input file";
        }
    }

    void run2()
    {
        run();
        uint16_t result_a = state["a"];
        state.clear();
        state["b"] = result_a;
        run();
    }

    uint16_t getState(string s){
        if (state.find(s) != state.end())
        {
            return state[s];
        }
        else
        {
            cout << "Data inavailable" << endl;
            return -1;
        }
    }



    static uint16_t doLogicOperation(string sin1, string sin2, uint16_t(*op)(uint16_t,uint16_t), bool& valid)
    {
        bool sub1_valid, sub2_valid;

        uint16_t in1 = getSubstrat(sin1, sub1_valid);
        uint16_t in2 = getSubstrat(sin2, sub2_valid);

        valid = sub1_valid && sub2_valid;
        //if (valid)
           //cout << sin1 << " (" << in1 << "), " << sin2 << " (" << in2 << ") |" << (valid ? "valid" : "not valid") << endl;
        return (*op)(in1,in2);
    }

    static uint16_t op_and(uint16_t in1, uint16_t in2)
    {
        //cout << __FUNCTION__ << endl;
        return in1 & in2;
    }

    static uint16_t op_or(uint16_t in1, uint16_t in2)
    {
        //cout << __FUNCTION__ << endl;
        return in1 | in2;
    }

    static uint16_t op_lshift(uint16_t in1, uint16_t in2)
    {
        //cout << __FUNCTION__ << endl;
        return in1 << in2;
    }

    static uint16_t op_rshift(uint16_t in1, uint16_t in2)
    {
        //cout << __FUNCTION__ << endl;
        return in1 >> in2;
    }

    static uint16_t op_xor(uint16_t in1, uint16_t in2)
    {
        //cout << __FUNCTION__ << endl;
        return in1^in2;
    }

    static uint16_t op_set(uint16_t in1, uint16_t in2)
    {
        //cout << __FUNCTION__ << endl;
        (void)in2;
        return in1;
    }

private:

    list<string> data;
    static map<string,uint16_t> state;

    static uint16_t getSubstrat(string& s, bool& valid)
    {
        uint16_t ret;
        if (state.find(s) != state.end())
        {
            valid = true;
            ret = state[s];
        }
        else if(s.length() > 0 && isdigit(s[0]))
        {
            valid = true;
            ret = (uint16_t)atoi(s.c_str());
        }
        else
        {
            valid = false;
            ret = -1;
        }

        return ret;
    }


    void remove_and_advance(list<string>::iterator& it)
    {
        list<string>::iterator tmp_it = it;
        ++it;
        data.erase(tmp_it);
    }

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

map<string,uint16_t> Interpreter::state;


int main()
{
    Interpreter interpreter("input");
    interpreter.run2();

    cout << "Result: " << interpreter.getState("a") << endl;

    return 0;
}
