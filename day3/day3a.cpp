#include <iostream>
#include <vector>
#include <fstream>

using Buffer = std::vector<char>;
typedef int64_t i64;

// :tr: we here using typedef, using, constexpr and define :tr:

#define MAX_PARAM_DIGIT_COUNT 3
constexpr int FUNCTION_NAME_LEN = 3;
constexpr char FUNC_NAME[FUNCTION_NAME_LEN] = { 'm','u','l' };


struct MulParams
{
    int x;
    int y;
};



static Buffer readFile()
{
    std::ifstream file("input.data", std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    Buffer buffer(size);
    if (!file.read(buffer.data(), size))
    {
        //guuuh something went wrong
        std::cerr << "ERROR: WAAAAAAAAAAAAAA.... mommyyyyyyyyyyyy\n";
    }

    return buffer;
}


static int str2int(const char* str, int len)
{
    //printf("%.*s\n", len, str);
    int i;
    int ret = 0;
    for (i = 0; i < len; ++i)
    {
        ret = ret * 10 + (str[i] - '0'); // :tr: 
    }
    return ret;
}


static int parseParam(const Buffer& buffer, i64& pos, char stopChar)
{
    const char* firstParamCharPos = &buffer[pos];
    int charCount = 0;

    char currentChar = buffer[pos];

    for (int i = 0; i < MAX_PARAM_DIGIT_COUNT; i++)
    {
        if (buffer[pos] == stopChar)
        {
            return str2int(firstParamCharPos, charCount);
        }

        if (!std::isdigit(buffer[pos]) || pos >= buffer.size())
        {
            return 0;
        }

        pos++;
        charCount++;
        currentChar = buffer[pos];
    }
    return str2int(firstParamCharPos, charCount);
}




static bool hasParams(const Buffer& buffer, i64& pos, i64& result)
{
    if (buffer[pos] != '(')
    {
        return false;
    }

    MulParams params{};
    pos++;
    params.x = parseParam(buffer, pos, ',');
    if (params.x == 0)
    {
        return false;
    }

    pos++;

    params.y = parseParam(buffer, pos, ')');
    if (params.y == 0 || buffer[pos] != ')')
    {
        return false;
    }

    pos++;
    result += params.x * params.y;
    return true;
}


static bool hasFunctionName(const Buffer& buffer, i64& pos)
{
    if (buffer[pos] != FUNC_NAME[0])
    {
        pos++;
        return false;
    }

    if (pos + 3 > buffer.size())
    {
        pos = buffer.size();
        std::cout << "INFO: Buffer ended. Can exit.\n";
        return false;
    }

    // we might have found the string
    for (int i = 1; i < FUNCTION_NAME_LEN; i++)
    {
        pos++;
        char currentChar = buffer[pos];
        if (buffer[pos] != FUNC_NAME[i])
        {
            pos++;
            return false;
        }

    }

    pos++;
    return true;
}


static i64 mulResult(const Buffer& buffer)
{
    i64 result = 0;
    char currentChar;
    i64 pos = 0;
    while (pos < buffer.size())
    {
        currentChar = buffer[pos];
        if (!hasFunctionName(buffer, pos))
        {
            continue;
        }

        if (!hasParams(buffer, pos, result))
        {
            continue;
        }

    }

    return result;
}

int main()
{
    Buffer buffer = readFile();
    const i64 output = mulResult(buffer);
    std::cout << "Output: " << output << "\n";

    //system("pause");
    return EXIT_SUCCESS;
}