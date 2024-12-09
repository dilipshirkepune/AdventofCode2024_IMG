#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;


int width;
int height;

map<char, vector<pair<int, int>>> processInputs(vector<string> inputs)
{
    map<char, vector<pair<int, int>>> data = {};
    int row = 0;
    for(auto line : inputs)
    {
        int col = 0;
        for(char ch : line)
        {
            if(ch != '.')
                data[ch].push_back({row, col});
            
            ++col;
        }
        ++row;
    }

    return data;
}

int getDistanceBetweenAntennas(int x1, int y1, int x2, int y2)
{
    int dist = 0;

    dist = sqrt(((x2 - x1) * (x2 - x1)) + (y2 - y1) * (y2 - y1));
    
    return dist;
}

bool checkWithinBoundingBox(int new_x, int new_y)
{
    return new_x >= 0 && new_x < width && new_y >= 0 && new_y < height;
}

void findAntiNodes(vector<pair<int, int>> antennas, set<pair<int, int>> &UniqueLoc)
{
    for(int i=0; i<antennas.size(); ++i)
    {
        for(int j=i+1; j<antennas.size(); ++j)
        {
            int dist_x = antennas[i].first -  antennas[j].first;
            int dist_y = antennas[i].second -  antennas[j].second;

            // +ve end of line
            int new_x = antennas[i].first + dist_x;
            int new_y = antennas[i].second + dist_y;

            if(checkWithinBoundingBox(new_x, new_y))
            {
                pair<int, int> tmp;
                tmp.first = new_x;
                tmp.second = new_y;
                UniqueLoc.insert(tmp);
            }    

            // -ve end of line
            new_x = antennas[j].first + dist_x;
            new_y = antennas[j].second + dist_y;
            if(checkWithinBoundingBox(new_x, new_y))
            {
                pair<int, int> tmp;
                tmp.first = new_x;
                tmp.second = new_y;
                UniqueLoc.insert(tmp);
                UniqueLoc.insert(tmp);
            } 
        }     
    }
}

int findLocations(map<char, vector<pair<int, int>>> data)
{
    set<pair<int, int>> UniqueLoc = {};

    for(auto eachFrequency : data)
    {
        vector<pair<int, int>> antennas = {};

        if((eachFrequency.second).size() > 1)
        {
            findAntiNodes(eachFrequency.second, UniqueLoc);
        }        
    }

    for(auto eachNode: UniqueLoc)
    {
        std::cout << eachNode.first << " " << eachNode.second << std::endl;
    }

    return UniqueLoc.size();
}  

int main()
{
    // parse file and prepare list of pairs <test value and numbers>
    std::ifstream infile("input8T.txt");
    string line = "";
    vector<string> inputs;
    map<char, vector<pair<int, int>>> data;
    bool flag = false;

    while(getline(infile, line))
    {
        if(!flag)
        {
            // it is set according to inputs for tests - may fail for other mixed lengh i/ps
            width = line.length();
            height = line.length();
            flag = true;
        }

        inputs.push_back(line);
    }

    // get input data - in structured format
    data = processInputs(inputs);

    // part 1
    int uniqueLoc = findLocations(data);    

    cout << "part 1: " << uniqueLoc << endl;

    return 0;
}