#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    //std::string str("xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))");
    //std::string str
    std::regex r("mul\\(\\d{1,3},\\d{1,3}\\)");
    std::regex r1("\\d{1,3}");  
    std::smatch m;
    vector<pair<int, int>> numbers;
    size_t sum = 0;

    std::ifstream infile("input3.txt");
    std::string str; 

    while (getline(infile, str))
    {
    
        while (std::regex_search (str, m, r)) 
        {
            for (auto x: m)
            {
                int a=0;
                int b=0;
                string local = x;
                std::smatch m1;

                //std::cout << x << " ";

                std::regex_search(local, m1, r1);
                for(auto n: m1)
                {
                    a = stoi(n);
                    //cout << n << " ";
                    local = m1.suffix().str();              
                    break;
                }

                std::regex_search(local, m1, r1);
                for(auto n: m1)
                {
                    b = stoi(n);
                    cout << n << " ";                
                }

                sum += a * b;    


            }
            //std::cout << std::endl;

            str = m.suffix().str();
        }        
  }
  cout << "sum = " << sum << endl;
}