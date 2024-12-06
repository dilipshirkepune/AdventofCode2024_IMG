#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

enum Direction 
{
    up = 0,
    down,
    right,
    left
};

int findGuardPos(string str, int& direction)
{
    int pos = string::npos;

    if(str.find('^') != string::npos)
    {
        pos = str.find('^');
        direction = Direction::up;        
    }
    else if((str.find('>') != string::npos))
    {
        pos = str.find('>');
        direction = Direction::right;
    }
    else if((str.find('<') != string::npos))
    {
        pos = str.find('<');
        direction = Direction::left; 
    }
    else if((str.find('v') != string::npos))
    {
        pos = str.find('v');
        direction = Direction::down; 
    }
    else
    {
        pos = string::npos;
        direction = -1;
    }
    
    return pos;
}

void changeDirection(int &dir)
{
    switch (dir)
    {
    case (Direction::up):
        /* code */
        dir = Direction::right;
        break;
    case (Direction::right):
        /* code */
        dir = Direction::down;
        break;
    case (Direction::left):
        /* code */
        dir = Direction::up;
        break;
    case (Direction::down):
        /* code */
        dir = Direction::left;
        break;    
    default:
        break;
    }
    
    return;
}

void walk(vector<string>& grid, int row, int col, int& dir, int& count)
{
    cout << "Walking..";
    for(int x=row; x<grid.size();)
    {
        for(int y=col; y<grid[x].length();)
        {
            // cout << x << "x" << y <<  "dir : " << dir << endl;
            
            if(dir == Direction::up)
            {
                if(x <= 0)
                    break;
                
                // check upside                 
                if(grid[x-1].at(y) != '.' && grid[x-1].at(y) != 'X')
                {
                    changeDirection(dir);                    
                }
                else
                {
                    if(grid[x].at(y) != 'X')
                    {
                        ++count;   
                        grid[x].at(y) = 'X';
                    }                    
                    
                    --x;
                    if(x <= 0)
                    {
                        ++count;   
                        grid[x].at(y) = 'X';
                        cout << " Walk complete : " << count << endl;
                        return;
                    }
                }                             
            }
            else if(dir == Direction::right)
            {
                
                if(y >= grid[x].length())
                    break;
                
                //check right
                if(grid[x].at(y+1) != '.' && grid[x].at(y+1) != 'X')
                {
                    changeDirection(dir);                    
                }
                else
                {
                    if(grid[x].at(y) != 'X')
                    {
                        ++count;
                        grid[x].at(y) = 'X';
                    }
                    
                    ++y;                    
                    if(y >= grid[x].length())
                    {
                        ++count;
                        grid[x].at(y) = 'X';

                        cout << " Walk complete : " << count << endl;
                        return;
                    }

                }
            }
            else if(dir == Direction::left)
            {
                
                if(y <= 0)
                    break;
                
                //check right
                if(grid[x].at(y-1) != '.' && grid[x].at(y-1) != 'X')
                {
                    changeDirection(dir);                    
                }
                else
                {
                    if(grid[x].at(y) != 'X')
                    {
                        ++count;
                        grid[x].at(y) = 'X';
                    }                    
                    --y;
                    
                    if(y <= 0)
                    {
                        ++count;
                        grid[x].at(y) = 'X';

                        cout << " Walk complete : " << count << endl;
                        return;
                    }
                }
            }
            else if(dir == Direction::down)
            {
                
                if(x >= grid.size()-1)
                    break;
                
                // check upside                 
                if(grid[x+1].at(y) != '.' && grid[x+1].at(y) != 'X')
                {
                    changeDirection(dir);                                        
                }
                else
                {
                    if(grid[x].at(y) != 'X')
                    {
                        ++count;
                        grid[x].at(y) = 'X';
                    }
                    ++x;
                    
                    if(x >= grid.size()-1)
                    {
                        grid[x].at(y) = 'X';
                        ++count;

                        cout << " Walk complete : " << count << endl;
                        return;
                    }                        
                } 
            }
            else
            {
                cout << "Invalid direction" << endl;
                return;
            }
        }
    }      
}


int main()
{

    std::ifstream infile("input6.txt");
    std::string str = "";     
    vector<string> grid = {};

    while (getline(infile, str))
    {
        grid.push_back(str);
    }

    int row = 0;
    int col = 0;
    int current_direction = -1;
    int count = 0;

    for(string line: grid)
    {
        col = findGuardPos(line, current_direction);
        if(col == string::npos)
        {
            row++;
            continue;
        }
        else
            break;
    }

    // cout << "Guard postion is = " << row  << "X" << col << " direction = " << current_direction << endl;

    walk(grid, row, col, current_direction, count);

    cout << "total steps walked = " << count << endl;


    // for(auto s: grid)
    // {
    //     cout << s << endl;
    // }

    return 0;   
}