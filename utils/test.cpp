#include "data.h"


int main()
{


    string filename = "test.csv";

    vector<vector<string>> data = 
    {{"t","hjasdjhf"},
    {"v","al;skjdffh"},
    {"l","asdlkjf"}};

    writeFile(filename, data);


    auto data_2 = readData(filename);

    displayDataFromReadData(data_2);

    return 0;
}