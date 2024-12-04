#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Function to search for all occurrences of "XMAS" in a word search grid
vector<pair<int, int>> findXMAS(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<pair<int, int>> locations;

    // Define all possible directions to search (horizontal, vertical, diagonal, and backwards)
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Start searching from each cell in the grid
            if (grid[i][j] == 'X') {
                for (int dir = 0; dir < 8; ++dir) {
                    int x = i, y = j, count = 0;
                    string word = "";

                    // Traverse in the current direction
                    while (x >= 0 && x < rows && y >= 0 && y < cols && count < 4) {
                        word += grid[x][y];
                        x += dx[dir];
                        y += dy[dir];
                        count++;
                    }

                    // Check if the formed word is "XMAS" or its reverse
                    if (word == "XMAS" || word == "SAMX") {
                        locations.push_back({ i, j }); // Store starting position of the word
                    }
                }
            }
        }
    }

    return locations;
}

// Function to search for all occurrences of "MAS" diagonally, backward forward in a word search grid
vector<pair<int, int>> findX_MAS(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<pair<int, int>> locations;

    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < cols - 2; ++j) {

            string word = "";
            string word1 = "";
            
            if(grid[i][j] == 'M' || grid[i][j] == 'S')
            {
                word += grid[i][j];
                word += grid[i + 1][j + 1]; 
                word += grid[i + 2][j + 2];
                word1 += grid[i][j+2];
                word1 += grid[i + 1][j + 1];
                word1 += grid[i + 2][j];

                if ((word == "MAS" || word == "SAM") && (word1 == "MAS" || word1 == "SAM"))
                {
                    locations.push_back({ i, j }); // Store the top-left corner of the "X"
                }
            }           
        }
    }

    return locations;
}


vector<pair<int, int>> findXMAS2(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<pair<int, int>> locations;

    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < cols - 2; ++j) {
            // Check for "MAS" or "SAM" in both diagonal directions
            if ((grid[i][j] == 'M' && grid[i + 1][j + 1] == 'A' && grid[i + 2][j + 2] == 'S') ||
                (grid[i][j] == 'S' && grid[i + 1][j + 1] == 'A' && grid[i + 2][j + 2] == 'M') ||
                (grid[i + 2][j] == 'M' && grid[i + 1][j + 1] == 'A' && grid[i][j + 2] == 'S') ||
                (grid[i + 2][j] == 'S' && grid[i + 1][j + 1] == 'A' && grid[i][j + 2] == 'M')) {
                locations.push_back({ i, j }); // Store the top-left corner of the "X"
            }
        }
    }

    return locations;
}



int main() {
    // vector<string> grid = {
    //     "MMMSXXMASM",
    //     "MSAMXMSMSA",
    //     "AMXSXMAAMM",
    //     "MSAMASMSMX",
    //     "XMASAMXAMM",
    //     "XXAMMXXAMA",
    //     "SMSMSASXSS",
    //     "SAXAMASAAA",
    //     "MAMMMXMMMM",
    //     "MXMXAXMASX"
    // };

    // vector<string> grid = {}; 
    // = {
    //     "....XXMAS.",
    //     ".SAMXMS...",
    //     "...S..A...",
    //     "..A.A.MS.X",
    //     "XMASAMX.MM",
    //     "X.....XA.A",
    //     "S.S.S.S.SS",
    //     ".A.A.A.A.A",
    //     "..M.M.M.MM",
    //     ".X.X.XMASX"
    // };

    // vector<string> grid = {
    //     "M.S",
    //     ".A.",
    //     "M.S"};
    
    std::ifstream infile("input4.txt");
    std::string str = "";     
    vector<string> grid = {};

    while (getline(infile, str))
    {
        grid.push_back(str);
    }

    // Part -1 
    vector<pair<int, int>> result = findXMAS(grid);
    cout << "PART2 : XMAS count :: " << result.size() << endl ;

    // Part -2 
    result = findX_MAS(grid);
    cout << "PART2 : XMAS count :: " << result.size() << endl ;    

    return 0;
}