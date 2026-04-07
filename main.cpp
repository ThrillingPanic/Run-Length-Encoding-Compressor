#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <utility>

bool readFile(std::string fileName, std::string &fileContents)
{
    char ch;
    std::ifstream file(fileName);
    if (file.is_open())
    {
        while (file.get(ch))
        {
            fileContents += ch;
        }
        file.close();
    }
    else
    {
        return 0;
    }
    return 1;
}

bool writeBin(std::string fileContents)
{
    std::vector<std::pair<int, char> > pairVector;
    char currentChar = fileContents[0];
    u_int8_t count = 0;
    for(u_long i = 0; i < fileContents.length(); i++){
        if(currentChar == fileContents[i]){
            count++;
        }else{
            pairVector.push_back(std::make_pair(count, currentChar));
            currentChar = fileContents[i];
            count = 1;
        }
    }
    pairVector.push_back(std::make_pair(count, currentChar));

    std::ofstream file("output.bin", std::ios::binary);
    count = 0;
    u_int8_t ch;
    if (file.is_open())
    {
        for (u_long i = 0; i < pairVector.size(); i++)
        {
            ch = pairVector[i].second;
            count = pairVector[i].first;
            file.write(reinterpret_cast<char*>(&count), 1);
            file.write(reinterpret_cast<char*>(&ch), 1);
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    std::string toCompress;
    std::cout << "Enter file name:" << "\n>> ";
    std::cin >> toCompress;
    std::string fileContents;

    if (readFile(toCompress, fileContents))
    {
        if (writeBin(fileContents))
        {
            std::cout << "Successfully wrote BIN file." << std::endl;
        }
        else
        {
            std::cout << "ERROR WRITING BIN FILE" << std::endl;
            return 0;
        }
    }

    else
    {
        std::cout << "ERROR READING FILE" << std::endl;
        return 0;
    }

    return 0;
}