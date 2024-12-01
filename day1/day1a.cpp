
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>


struct InputData
{
    std::vector<int> left, right;
};


const uint32_t countLines(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    return std::count(std::istreambuf_iterator<char>(file),
                      std::istreambuf_iterator<char>(), '\n');
}


bool readData(InputData& data)
{
    std::string filename = "input.data";
    const uint32_t lineCount = countLines(filename);

    data.left.reserve(lineCount);
    data.right.reserve(lineCount);

    std::ifstream inputFile(filename);

    if (!inputFile)
    {
        std::cerr << "wahhh?\n";
        return false;
    }

    int left, right;
    while (inputFile >> left >> right)
    {
        data.left.push_back(left);
        data.right.push_back(right);
    }

    inputFile.close();
    return true;
}


const int computeSimilarityScore(const InputData& data)
{
    int distance = 0;
    for (int index = 0; index < data.left.size(); index++)
    {
        distance += std::abs(data.left[index] - data.right[index]);
    }

    return distance;
}


int main()
{
    InputData data;

    if (!readData(data))
    {
        std::cerr << "Error on reading the file!\n";
        return EXIT_FAILURE;
    }
    
    std::sort(data.left.begin(),data.left.end());
    std::sort(data.right.begin(),data.right.end());

    const int totalDistance = computeSimilarityScore(data);

    std::cout << "Total Distance: " << totalDistance << "\n";
    system("pause");
}