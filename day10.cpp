#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;

int trails;

pair<int, int> getNext(vector<string> &map, pair<int, int> &currLoc, int &dir)
{
    int row = currLoc.first;
    int col = currLoc.second;   
    pair<int, int> next;

    if(dir == 0)    //right
    {        
        if(col == (map[row].length()-1)) // reached to end of line - now move down
        {
            dir = 1;
            ++row;
        }
        else
        {
            ++col;
        }

    }
    else if(dir == 1)
    {
        if(row == (map.size() -1))      // reached to bottom of the map - change dir left
        {
            dir = 2;
            --col;
        }
        else
        {            
            ++row;
        }

    }
    else if(dir == 2)
    {        
        if(col == 0)    // reached to the extrem left - change dir to up
        {
            dir = 3;
            --row;            
        }
        else
        {
            --col;
        }
    }
    else if(dir == 3)
    {        
        if(row == 0)    // reached to the top of map - change dir to right
        {
            dir = 0;
            ++col;
        }
        else
        {
            --row;
        }
        
    }
    
    next.first = row;
    next.second = col;

    return next;    
}

struct lastNode 
{
    pair<int, int> pos;
    int dir;
};
vector <struct lastNode> path = {};
void walk(vector<string> &map, pair<int, int> start, int direction, set<pair<int, int>> &visited)
{
    if((direction > 3 || map[start.first][start.second] == '9'))  // || ((start.first >= (map.size()-1)) && (start.second >= map[start.first].length()-1)))
    {
        if((map[start.first][start.second] == '9') && visited.find(start) == visited.end())
        {
            ++trails;
            visited.insert(start);  
            cout << " found = " << start.first << " " << start.second << endl;

            if(direction == 0)
            {
                if((start.second+1) < map[start.first].length() && ((map[start.first][start.second+1]) == '9'))
                    ++trails;
            }
            else if(direction == 1)
            {
                if((start.first+1) < map.size() && ((map[start.first+1][start.second]) == '9'))
                    ++trails;

            }
            else if(direction == 2)
            {
                if(((start.second-1) > 0) && ((map[start.first][start.second-1]) == '9'))
                    ++trails;
            }
            else if(direction == 3)
            {
                if(((start.first-1) > 0) && ((map[start.first-1][start.second]) == '9'))
                    ++trails;
            }
        }        
        return;
    }


    char curr = map[start.first][start.second];
    std::cout << curr << " ";
    int previous = direction;
    pair<int, int> nextPos = getNext(map, start, direction);
    char next = map[nextPos.first][nextPos.second];
 
    
    if((next - curr) == 1)
    {      
        lastNode node;
        node.pos = start;
        if(previous != direction)
        {
            node.dir = direction;
            cout << "direction changed" << endl;
        }
        else
        {
            node.dir = previous;
        }
        

        path.push_back(node);

        if(visited.find(nextPos) != visited.end())
            ++direction;      
        walk(map, nextPos, direction, visited);        
    }
    else
    {
        ++direction;
        walk(map, start, direction, visited);
    }
     
        
    if(!path.empty())
    {
        lastNode node;
        node = path.back();
        path.pop_back();

        start = node.pos;
        direction = node.dir;

        ++direction;
        if(direction > 3)
        {   
            //path.pop_back();
            return;
        }
        else
            walk(map, start, direction, visited);
    }            
  
    
    return;    
}


int walk1(vector<string> &map, pair<int, int> start, int direction, set<pair<int, int>> &visited)
{
    int result;
    if( visited.find(start) != visited.end())
    {
            
        return 0;
    }

    cout << map[start.first][start.second] << " ";
    visited.insert(start);        

    if(map[start.first][start.second] == '9')
        return 1;

    result = 0;

    for(int i=0; i<4; ++i)
    {
        pair<int, int> nextPos;
        nextPos = getNext(map, start, direction);
        char next = map[nextPos.first][nextPos.second];
        result += walk1(map, nextPos, direction, visited);
    }

     
    return result;
}

int main()
{
    // parse file and prepare list of pairs <test value and numbers>
    std::ifstream infile("input10T.txt");
    string line = "";
    vector<string> map;   
    
    while(getline(infile, line))
    {
        map.push_back(line);
    }

    int row = 0;

    for(auto line: map)
    {   
        int col = 0;
        
        for(auto element: line)
        {
            //cout << map[row][col] << " " << endl;
            pair<int, int> location = {};
            location.first = row;
            location.second = col;
            int direction = 0;
            set <pair<int, int>> visited = {};

            if(element == '0')
            {
                int trails1 = walk1(map, location, direction, visited);
                std::cout << "Trails = " << trails1 << endl;
                //trails = 0;
            }
            // goto next col
            ++col;
        }
        // goto next row
        ++row;
    }

    

    return 0;
}
