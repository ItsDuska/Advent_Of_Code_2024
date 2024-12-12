#include <iostream>
#include <vector>
#include <fstream>

using Buffer = std::vector<char>;
typedef int64_t i64;
typedef uint64_t u64;

constexpr int WORD_LEN = 4;
constexpr char XMAS[4] = { 'X','M','A','S' };

struct Vec2i
{
    i64 x;
    i64 y;

    const Vec2i operator*(const int& multiplier) const
    {
        Vec2i result;
        result.x = x * multiplier;
        result.y = y * multiplier;
        return result;
    }
};



Buffer readFile()
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

const Vec2i calculateBoxSize(Buffer& buffer)
{
    Vec2i box = {};

    while (buffer[box.x] != '\n')
    {
        box.x++;
    }
    box.x++;

    box.y = buffer.size() / box.x;

    return box;
}


Vec2i calcNewPosition(i64 index, const Vec2i& direction, const Vec2i& box)
{
    const int row = index / box.x;
    const int col = index % box.x;

    Vec2i result;
    result.y = row + direction.y;
    result.x = col + direction.x;

    return result;
}

u64 toIndex(const Vec2i& position, i64 maxCols)
{
    return (position.y * maxCols) + position.x;
}

bool validBoxPosition(i64 index, const Vec2i& direction, const Vec2i& box, const Buffer& buffer)
{
    const Vec2i newPosition = calcNewPosition(index, direction, box);
    const u64 charIndex = toIndex(newPosition, box.x);

    if (charIndex >= buffer.size())
    {
        return false;
    }

    return (buffer[charIndex] == 'S');
}

bool validWord(const Buffer& buffer, i64 index, const Vec2i direction, const Vec2i& box)
{
    for (int i = 1; i < WORD_LEN-1; i++)
    {
        const Vec2i currentDirection = direction * i;
        const Vec2i newPosition = calcNewPosition(index, currentDirection, box);

        const u64 newIndex = toIndex(newPosition, box.x);

        const char currentChar = buffer[newIndex];

        if (currentChar != XMAS[i])
        {
            return false;
        }
    }
    return true;
}


constexpr Vec2i DIRECTIONS[8] = { {1,1}, {1,0}, {-1,0}, {-1,-1}, {-1,1},    {0,-1}, {0,1},     {1,-1} };

const u64 xmasCount(Buffer& buffer, const Vec2i& box)
{
    i64 count = 0;
    for (i64 index = 0; index < buffer.size(); index++)
    {
        if (buffer[index] != XMAS[0])
        {
            continue;
        }

        for (const Vec2i& direction : DIRECTIONS)
        {
            const Vec2i newDirection = direction * (WORD_LEN-1);

            if (!validBoxPosition(index, newDirection, box, buffer))
            {
                continue;
            }
            
            if (!validWord(buffer, index, direction, box))
            {
                continue;
            }

            // we found XMAS word
            count++;
        }
    }

    return count;
}

int main()
{
    Buffer buffer = readFile();
   
    const Vec2i box = calculateBoxSize(buffer);
    const i64 result = xmasCount(buffer, box);
    std::cout << "Result: " << result << "\n";

    system("pause");
    return EXIT_SUCCESS;
}