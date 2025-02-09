#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


int writeFile(string path, vector<vector<string>> data)
{

    ofstream openFile(path);

    if (!openFile) 
    {
        cerr << "Error opening file, ensure file exists!" << endl;
        return 1;
    }

    
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            openFile << row[i];
            if (i < row.size() - 1) {
                openFile << ",";  // Separate by commas
            }
        }
        openFile << endl;  // New line for the next row
    }

    openFile.close();  // Close the file


    return 0;

}


vector<vector<string>> readData(string path)
{
    ifstream readFile(path);

    vector<vector<string>> data;



    if (!readFile) {
        cerr << "Error opening file for reading ensure it exists" << endl;
        return data;
    }

    string line;

    while(getline(readFile, line))
    {
        stringstream ss(line);
        string cell;

        vector<string> row;


        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    readFile.close();

    return data;
}

void displayDataFromReadData(vector<vector<string>> data)
{
    for (const auto& row : data) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}







