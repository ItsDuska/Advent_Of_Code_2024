#include <iostream>
#include <vector>
#include <fstream>

using Buffer = std::vector<char>;
typedef int64_t i64;
typedef uint64_t u64;


struct Vec2i
{
    i64 x;
    i64 y;
};

constexpr Vec2i STARTING_OFFSETS[2] = {{-1,-1}, {-1,1}};
constexpr Vec2i ENDING_OFFSETS[2] = {{1,1}, {1,-1}};

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

char getCharacter(i64 index, const Vec2i& direction, const Vec2i& box, const Buffer& buffer)
{
    const Vec2i newPosition = calcNewPosition(index, direction, box);
    const u64 charIndex = toIndex(newPosition, box.x);

    if (charIndex >= buffer.size())
    {
        return '.';
    }

    return buffer[charIndex];
}

bool isXmas(const Buffer& buffer, i64 index, const Vec2i& box)
{
    for (int i = 0; i < 2; i++)
    {
        char first = getCharacter(index,STARTING_OFFSETS[i],box,buffer);
    
        if (first == '.')
        {
            return false;
        }
    
        char last = getCharacter(index,ENDING_OFFSETS[i],box,buffer);

        if (last == '.')
        {
            return false;
        }
    
        if (!(first == 'M' && last == 'S') && !(first == 'S' && last == 'M'))
        {
            return false;
        }
    }
    
    return true;
}

const u64 xmasCount(Buffer& buffer, const Vec2i& box)
{
    i64 count = 0;
    for (i64 index = 0; index < buffer.size(); index++)
    {
        if (buffer[index] != 'A')
        {
            continue;
        }

        if (!isXmas(buffer,index,box)) 
        {
            continue;
        }       

        // we found XMAS word
        count++;
        
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
