
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

void processStr(vector<int> &rearragedMap)
{
    std::ifstream infile("input9.txt");
    char ch;    
    int index=0;
    size_t blockID = 0;
    while (infile >> ch) 
    {
        unsigned int count = int (ch - 0x30);
        while(count)
        {
            if(index%2)
            {
                rearragedMap.push_back(-1); 
            }
            else
            {
                rearragedMap.push_back(blockID);
            }
            --count;
        }
        if(!(index%2))
            ++blockID;   
        ++index;
    }   
}

unordered_map<int, vector<int>> count_repeated_numbers(const vector<int>& nums) 
{
    unordered_map<int, int> counts;
    unordered_map<int, vector<int>> repeated_nums;

    for (int i = 0; i < nums.size(); ++i) 
    {

        int num = nums[i];
        if (counts.count(num)) 
        {
            counts[num]++;
            repeated_nums[num].push_back(i);
        } 
        else 
        {
            counts[num] = 1;
            repeated_nums[num] = {i}; 
        }
    }

  return repeated_nums;
}

vector <pair <int, int>> checkemptyspaces(vector<int> &spaceIndex, vector<int> &rearragedMap)
{

    vector <pair <int, int>> spaceIndexCount = {};
    //for(int index = 0; index < spaceIndex.size();)
    int prv = 0;
    for(auto index : spaceIndex)
    {
        if(prv > index)
        {
            continue;
        }
        
        int count = 0;
        int tmp = index;
        while(rearragedMap[index] == -1 && index < rearragedMap.size())
        {
            ++count;
            ++index;
        }
        pair<int, int> tmpPair;
        tmpPair.first = count;
        tmpPair.second = tmp;
        prv = index;

        spaceIndexCount.push_back(tmpPair); 
    }
    return spaceIndexCount;
}

bool checkemptyspaceforkey(int size, int present_index, vector <pair <int, int>> &spaceIndexCount)
{
    for(auto entry: spaceIndexCount)
    {
        if(entry.first >= size && entry.second < present_index)
        {
            return true;
        }               
    }
    
    return false;
}

void rearrangeblocks2(vector<int> &rearragedMap, unordered_map<int, vector<int>> &repeated_nums)
{
    // iterate over list and find space
    vector<int> spaceIndex = repeated_nums[-1];

    // Vector to store the keys
    vector<int> keys;

    // Extract keys using a loop
    for (auto it = repeated_nums.begin(); it != repeated_nums.end(); ++it)
    {
        // Add the key to the vector
        if(it->first != -1)
            keys.push_back(it->first);
    }

    sort(keys.begin(), keys.end(), greater<>());
    
    vector <pair <int, int>> spaceIndexCount;
    spaceIndexCount = checkemptyspaces(spaceIndex, rearragedMap);

    // rearrange numbers
    for(int i=0; i<spaceIndexCount.size();)
    {
        bool flag = false;
        // check right sized block
        std::vector<int>::iterator rit = keys.begin();
        for(int k=0; k<keys.size(); ++k)
        {
            
            if(spaceIndexCount[i].first >= repeated_nums[*rit].size())
            {
                int present_index;
                //cout << "found block of size " << *rit << " with space " << repeated_nums[*rit].size() << endl;
                for(int j=0; j<repeated_nums[*rit].size(); j++)
                {
                    present_index = spaceIndexCount[i].second + j;
                    rearragedMap[present_index] = *rit;
                    rearragedMap[repeated_nums[*rit][j]] = -1; 
                    //cout << std::distance(keys.begin() - rit);
                    flag = true;                                        
                }
                if(flag)
                {
                    // check if space for key is available or not - if not then remove key from list
                    spaceIndexCount = checkemptyspaces(spaceIndex, rearragedMap);
                    if (checkemptyspaceforkey(repeated_nums[*rit].size(), present_index, spaceIndexCount) == false)
                    {
                        keys.erase(find(keys.begin(), keys.end(), *rit)); 
                    }
                    i++;
                   flag = false;
                   rit = keys.begin();                       
                }
            }  
            else
            {
                rit++;
            }
        }

        cout << endl;
    }
   
}

void rearrangeblocks(vector<int> &rearragedMap)
{
    int index = 0;
    int spaces = 0;
    int size = rearragedMap.size();
    for(auto item : rearragedMap)
    {
        if(item == -1)
        {
            while(rearragedMap.back() == -1)
            {
                ++spaces;
                rearragedMap.pop_back();
            }
            
            if(rearragedMap.back() != -1)
            {
                ++spaces;                
                rearragedMap[index] = rearragedMap.back();
                rearragedMap.pop_back();
            }
                       
        }
        ++index;

        if(spaces + index == size)
            break;
    }
    while(spaces)
    {
        rearragedMap.push_back(-1);
        --spaces;
    }
}

void calculateCheckSum(vector<int> &rearragedMap, long long &checksum)
{
    for(int i=0; i<rearragedMap.size(); ++i)
    {        
        if(rearragedMap[i] != -1)
        {
            int sum = i * (rearragedMap[i]);
            checksum += sum;
        }       
    }
}


int main()
{
    // parse file and prepare list of pairs <test value and numbers>    
    vector<int> rearragedMap = {};

    // unfold 
    processStr(rearragedMap);

    // for part-2 keep meta data    
    unordered_map<int, vector<int>> repeated_nums;
    repeated_nums = count_repeated_numbers(rearragedMap);

    // move blocks
    rearrangeblocks(rearragedMap);

    // Part -2 
    //rearrangeblocks2(rearragedMap, repeated_nums);

   // checksum
   long long checksum = 0;
   
   calculateCheckSum(rearragedMap, checksum);

   cout << "Checksum = " << checksum << endl;

    return 0;
}