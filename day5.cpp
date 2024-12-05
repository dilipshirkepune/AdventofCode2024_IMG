#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;



map<int, vector<int>> getPageOrderRules(vector<string> data)
{
    map<int, vector<int>> rules = {};
    std::regex r1("\\|");
    std::smatch match;  
    
    for(auto entry: data)
    {
        int key;
        vector<int> pages;
        std::regex_search(entry, match, r1);
        key = stoi(match.prefix());
        rules[key].push_back(stoi(match.suffix()));
    }

    return rules;
}

vector<vector<int>> getUpdates(vector<string> data)
{
    vector<vector<int>> updates = {};
    //std::string str; 
    //while (getline(infile, str))
    for(auto entry: data)
    {
        vector <int> level = {};
        stringstream ss(entry);
        int number;
        while(ss >> number)
        {
            level.push_back(number);
            if (ss.peek() == ',')
                ss.ignore();            
        }
        updates.push_back(level);        
    }

    return updates;
}

vector<vector<int>> getUpdatesPart2(vector<string> data)
{
    vector<vector<int>> updates = {};    
    for(auto entry: data)
    {
        vector <int> level = {};
        stringstream ss(entry);
        int number;
        while(ss >> number)
        {
            level.push_back(number);
            if (ss.peek() == ',')
                ss.ignore();            
        }
        updates.push_back(level);        
    }

    return updates;
}

bool checkordering(map<int, vector<int>> &rules, vector<int> pages)
{
    bool result = true;
    map<int,vector<int>>::iterator it;
    static int row;
    bool inOrder = true;
    
    for(int index=0; index<pages.size(); ++index)
    {
        
        int key = pages[index];
        it = rules.find(key);
        if (it == rules.end() && key != pages.back())
        {
            inOrder = false;
            break;
        }
            

        for(int next=index+1; next<pages.size(); next++)
        {
            if(std::find((it->second).begin(), (it->second).end(), pages[next]) != (it->second).end())
            {
                continue;
            }
            else
            {
                inOrder = false;
                break;
            }
        }
      
        if(!inOrder)
            break;        
    }

    return inOrder;
}

bool checkordering1(map<int, vector<int>> &rules, vector<int> &pages)
{
    bool result = true;
    map<int,vector<int>>::iterator it;
    static int row;
    bool inOrder = true;
    
    for(int index=0; index<pages.size(); ++index)
    {
        
        int key = pages[index];
        it = rules.find(key);        
        
        // Key without pages
        if (it == rules.end() && key != pages.back())
        {
            //Key without pages so swap the current page with next page and recheck
            int tmp =  pages[index+1];
            pages[index+1] = pages[index];
            pages[index] = tmp;
            index--;
            continue;            
        }
        
        // Find right ordered page
        // find list indexed page
        int min = index+1;      
        for(int next=index+1; next<pages.size(); next++)
        {
            if(std::find((it->second).begin(), (it->second).end(), pages[next]) != (it->second).end())
            {
                 if (min > next)
                 {                   
                    int tmp = pages[min];
                    pages[min] = pages[next];
                    pages[next] = pages[min];
                    min = next;
                 }                   
                 else
                    continue;   
            }
            else
            {
                int tmp = pages[index];
                pages[index] = pages[next];
                pages[next] = tmp;                
                --index;
                break;
            }
        }   

    }
           
    
    return inOrder;
}



int main()
{
    // vector <string> data = {
    // "47|53",
    // "97|13",
    // "97|61",
    // "97|47",
    // "75|29",
    // "61|13",
    // "75|53",
    // "29|13",
    // "97|29",
    // "53|29",
    // "61|53",
    // "97|53",
    // "61|29",
    // "47|13",
    // "75|47",
    // "97|75",
    // "47|61",
    // "75|61",
    // "47|29",
    // "75|13",
    // "53|13"};


    // vector <string> update_data = {
    //     "75,47,61,53,29",
    //     "97,61,53,29,13",
    //     "75,29,13",
    //     "75,97,47,61,53",
    //     "61,13,29",
    //     "97,13,75,29,47"
    // };



    map<int, vector<int>> rules = {};
    vector<vector<int>> updates = {};
    bool flag = false;
    int sum = 0;
    

    std::ifstream infileRules("rules.txt");
    std::ifstream infileUpdates("updates.txt");
    std::string str = "";     
    vector <string> data = {};
    vector <string> update_data = {};

    while (getline(infileRules, str))
    {
        data.push_back(str);
    }

    while (getline(infileUpdates, str))
    {
        update_data.push_back(str);
    }



    rules = getPageOrderRules(data);
    //Part 1
    updates = getUpdates(update_data);

    for(auto eachUpdate: updates)
    {
        flag = checkordering(rules, eachUpdate);
        
        if(flag)
        {            
            sum += eachUpdate[(eachUpdate.size()/2 + eachUpdate.size()%2)-1];
        }
    }
    

    //Part 2
    updates = getUpdatesPart2(update_data);
    int inCorrectSum = 0;
    for(auto eachUpdate: updates)
    {
        flag = checkordering(rules, eachUpdate);
        
        if(!flag)
        {
            flag = checkordering1(rules, eachUpdate);            
            inCorrectSum += eachUpdate[(eachUpdate.size()/2 + eachUpdate.size()%2)-1];
        }        
    }   

    cout << "sum = " << sum << endl;
    cout << "inCorrectSum = " << inCorrectSum << endl;

    return 0;
}