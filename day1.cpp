//#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;


int main()
{

    // test data
/*  "3   4
    4   3
    2   5
    1   3
    3   9
    3   3"
*/
    vector<int> left = {};
    vector<int> right = {};
    int dist = 0;
    int a;
    int b;

    std::ifstream infile("input.txt");
    while (infile >> a >> b)
    {
        left.push_back(a);
        right.push_back(b);
    }


    
    stable_sort(left.begin(), left.end());
    stable_sort(right.begin(), right.end());

    int Lsize = left.size();
    int Rsize = right.size();

    cout << Lsize << " " << Rsize << endl;

    if(Lsize <= Rsize)
    {
        for(int i=0; i<Lsize; i++)
        {
            // Puzzle 1
            //dist += abs(left[i] - right[i]) ;
            // Puzzle 2
            dist += left[i] * (count(right.begin(), right.end(), left[i]));
        }
    }
    cout << "dist = " << dist << endl;
    
    return 0;
}