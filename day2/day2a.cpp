#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

using InputData = std::vector<std::vector<int>>;


const uint32_t countLines(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    return std::count(std::istreambuf_iterator<char>(file),
                      std::istreambuf_iterator<char>(), '\n');
}


InputData readFile()
{
    InputData data;

    const std::string filename = "input.data";
    data.reserve(countLines(filename));

    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        std::cerr << "waaaaaahhhh :wehweh:\n";
        return data; // waaaaa.
    }

    std::string currentLine;
    while (std::getline(inputFile, currentLine))
    {
        std::vector<int> row;
        row.reserve(8);

        std::stringstream stream(currentLine);
        int num;
        while (stream >> num)
        {
            row.push_back(num);
        }
        data.push_back(row);
    }

    inputFile.close();
    return data;
}

const uint32_t countReportSafetyAmount(const InputData& inputData)
{
    uint32_t safeReportCount = 0;
    for (const std::vector<int>& level : inputData)
    {
        bool isSafe = true;

        const bool decreasing = (level[0] > level[1]);
        
        for (int i = 0; i < level.size() - 1; i++)
        {
        if ((level[i] < level[i+1] && decreasing) || (level[i] > level[i+1] && !decreasing))
        {
            isSafe = false;
            break;  
        }

        const int val = std::abs(level[i] - level[i+1]);
        if (val == 0 || val > 3)
        {
            isSafe = false;
            break;
        }
    }

    if (isSafe)
    {
        safeReportCount++;
    }
    }
    
    return safeReportCount;
}


int main()
{
    InputData inputData = readFile();

    if (inputData[0].empty())
    {
        return EXIT_FAILURE;
    }

    const uint32_t output = countReportSafetyAmount(inputData);
    std::cout << "Output: " << output << "\n";
    system("pause");
    return EXIT_SUCCESS;
}