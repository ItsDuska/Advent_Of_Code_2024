
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>


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
    std::unordered_map<int, int> rightCountMap;
    for (int num : data.right)
    {
        rightCountMap[num]++;
    }

    int similarityScore = 0;
    for (int num : data.left)
    {
        int countInRight = rightCountMap[num];
        similarityScore += num * countInRight;
    }

    return similarityScore;
}


int main()
{
    InputData data;

    if (!readData(data))
    {
        std::cerr << "Error on reading the file!\n";
        return EXIT_FAILURE;
    }
    
    const int score = computeSimilarityScore(data);

    std::cout << "Total Distance: " << score << "\n";
    system("pause");
}