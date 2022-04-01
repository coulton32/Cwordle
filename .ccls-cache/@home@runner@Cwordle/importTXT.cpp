#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
void loadFile(std::string fileName)
{
    std::vector<std::string> fileContents;
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) return;

    std::string word;
    while (file >> word)
    {
        fileContents.push_back(word);
    }

    for (int i = 0; i < fileContents.size(); i++)
    {
        cout << fileContents[i] << endl;
    }  
}