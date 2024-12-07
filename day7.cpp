#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

#define PART2   false

using namespace std;



map<long long, vector<int>> getData(vector<string> inputs)
{
    map<long long, vector<int>> data = {};
    std::regex r1("\\:");
    std::smatch match;  
    
    for(auto entry: inputs)
    {
        long long test_val;
        vector<int> numbers = {};        
        int number;

        regex_search(entry, match, r1);
        test_val = stoll(match.prefix());
        
        stringstream ss(match.suffix());        
        while(ss >> number)
        {
            numbers.push_back(number);
            if (ss.peek() == ' ')
                ss.ignore();            
        }

        data[test_val] = numbers;
    }

    return data;
}

void getPermutations(string prefix, int n, vector<string> &ops)
{
    if(n == 0)
    {
        ops.push_back(prefix);
        return;
    }

    getPermutations(prefix + "+", n-1, ops);
    getPermutations(prefix + "*", n-1, ops);

#ifdef PART2
    getPermutations(prefix + "|", n-1, ops);
#endif

}

long long makeEquation(string token, vector<int>numbers)
{
    int i = 0;
    long long result = numbers[i];

    for(auto ch: token)
    {
        if(ch == '+')
            result += numbers[i+1];
        else if(ch == '*')
            result *= numbers[i+1];
#ifdef PART2            
        else if(ch == '|')
        {
            string tmp = to_string(result) + to_string(numbers[i+1]);
            result = stoll(tmp);            
        }
#endif
        i++;                        
    }

    return result;
}


long long checkNumbers(const map<long long, vector<int>> data)
{
    long long sum = 0;
    

    // loop over all entries in map
    for(auto entry : data)
    {
        vector<string> ops = {};
        // fetch test value and numbers
        long long test_val = entry.first;
        vector<int> numbers = entry.second;

        // number of operations
        int operations = numbers.size() - 1; 
        
        // get the number of permutations of operations 
        getPermutations("", operations, ops);

        // loop over permulations and apply over numbers
        for(auto token: ops)
        {          
            if (makeEquation(token, numbers) == test_val)
            {
                sum += test_val;
                cout << "matched :" << test_val << " " << sum << endl;
                break;
            }            
        }
    }

    return sum;
}


int main()
{
    // parse file and prepare list of pairs <test value and numbers>
    std::ifstream infile1("input7.txt");
    string line = "";
    map<long long, vector<int>> data = {};
    vector<string> inputs;
    long long sum = 0;

    while(getline(infile1, line))
    {
        inputs.push_back(line);
    }

    // get data from input.txt 
    data = getData(inputs);

    // check if number are able to make test value.
    sum = checkNumbers(data);

    // result
    cout << "sum = " << sum << endl;
    return 0;
}

