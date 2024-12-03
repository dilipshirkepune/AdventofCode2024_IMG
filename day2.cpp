#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
string reason = "";

bool isLevelSafe(vector <int> level)
{    
    bool inc=false, des=false;
    int flag = 0;
    
    for(int j = 1; j < level.size(); j++)
    {
        int diff = abs(level[j] - level[j-1]);
        //cout << "diff = " << diff <<  endl;
        if(diff == 0 || diff > 3)
        {
            //cout << "1 unsafe" << endl;
            reason = "1 Equal or diff more than 3";
            flag+=1;
            break;
        }
        
        if(level[j] > level[j-1] && j==1)
        {
            inc = true;
        }
        else if(level[j] <= level[j-1] && inc != false)
        {
            //cout << "2 unsafe" << endl;
            reason = "ascending order not maintained.";
            flag+=1;
            break;
        }
        else if(level[j] < level[j-1] && j==1)
        {
            des = true;
        }
        else if(level[j] >= level[j-1] && des != false)
        {
            //cout << "3 unsafe" << endl;
            reason = "descending order not maintained.";
            flag+=1;
            break;
        }
    }

    if(flag == 0)
        return true;
    else
        return false;
}

vector <int> removefirstProblem(vector <int> &level)
{    
    bool inc=false, des=false;
    int problem = 0;
    
    for(int j = 1; j < level.size(); j++)
    {
        int diff = abs(level[j] - level[j-1]);
        //cout << "diff = " << diff <<  endl;
        
        if(diff == 0)
        {
            level.erase(level.begin()+(j));
            return level;
        }
                
        if(level[j] > level[j-1] && j==1)
        {
            inc = true;
            continue;
        }
        else if(level[j] < level[j-1] && j==1)
        {
            des = true;
            continue;
        }
        else if(diff > 3 && (inc != false || des != false))
        {
            vector<int> temp = level;
            temp.erase(temp.begin()+(j));
            if(isLevelSafe(temp))
            {
                return temp;
            }
            else
            {
                temp = level;
                temp.erase(temp.begin()+(j-1));   
                if(isLevelSafe(temp))
                {
                    return temp;
                }
            }
            return level;
        }       
    }
    return level;    
}

int main()
{
    vector<vector <int>> report = {};
    std::ifstream infile("input2.txt");    
    int a, b, c, d, e, f;
    int safe = 0;

    std::string str; 
    while (getline(infile, str))
    {
        vector <int> level = {};
        stringstream ss(str);
        int number;
        while(ss >> number)
        {
            level.push_back(number);
        }
        report.push_back(level);        
    }
    
    // for(auto i: report)
    // {
    //     for(auto j: i)
    //     {
    //     cout << j << " ";
    //     }
    //     cout << endl;       
    // }

        for(auto level: report)
        {
            if(!isLevelSafe(level))
            {
                cout << "before : ";
                for(auto j: level)
                {
                    cout << j << " ";
                }
                cout << endl;

                removefirstProblem(level);
                
                cout << "After : " ;
                for(auto j: level)
                {
                    cout << j << " ";
                }
                

                if(isLevelSafe(level))
                {
                    safe += 1;
                    cout << " Safe : "  << safe << endl;
                }
                else
                {
                    cout << " unsafe :" << reason << endl;
                }
                    
            }
            else
            {
                safe += 1;
            }
                            
        }

    
    cout << "safe = " << safe << endl << endl;

    return 0;
}

