#include <iostream>
#include <vector>
#include <ranges>
#include <string>
#include <span>
#include <fstream>
#include <sstream>
#include <print>

class ImageData
{
private:
    char magic_number[2];
    int width;
    int hight;
    short maxval;
    std::string file_contents;
    using ColorViewType = decltype(std::declval<std::span<unsigned char>>() | std::views::drop(0) | std::views::stride(3));
    std::optional<ColorViewType> red, green, blue;

    std::string readFile(const std::string &file_path)
    {
        std::ifstream file(file_path); // reads the file
        std::ostringstream string_stream;
        string_stream << file.rdbuf(); // streams it into a string stream
        return string_stream.str();    // turns the stream into a string
    }

    void skipWhitespace(int &string_position)
    { // updates string position to end of whitespace
        while (isspace(file_contents[string_position]))
        {
            string_position++;
        }
    }

    int getDecimalFromString(int &string_position)
    { // returns the decimal, or 0 if it fails. keeps string position updated
        int starting_position = string_position;
        std::string string_of_decimal;
        while (!isspace(file_contents[string_position]))
        {
            string_position++;
        }
        try
        {
            return std::stoi(file_contents.substr(starting_position, string_position));
        }
        catch (...)
        {
            return 0;
        }
    }

public:
    ImageData(const std::string &file_path)
    {
        file_contents = readFile(file_path);
        int string_position = 0; // helps to keep track of where I'm at while extracting data

        // get the magic number
        magic_number[0] = file_contents[0];
        string_position++;
        magic_number[1] = file_contents[1];
        string_position++;
        skipWhitespace(string_position);

        // get width
        width = getDecimalFromString(string_position);
        skipWhitespace(string_position);
        // get hight
        hight = getDecimalFromString(string_position);
        skipWhitespace(string_position);

        // get maxval
        maxval = getDecimalFromString(string_position);
        if (maxval < 0 || maxval >= 65536)
        {
            maxval = 0;
        }

        string_position++; // next char should be whitespace

        // create red, green, and blue views
        std::span<unsigned char> full_file(reinterpret_cast<unsigned char *>(file_contents.data()), file_contents.size()); // gotta read it differently (unsigned)
        std::span<unsigned char> bytes = full_file.subspan(string_position);
        // red
        red = bytes | std::views::drop(0) | std::views::stride(3);
        // green
        green = bytes | std::views::drop(1) | std::views::stride(3);
        // blue
        blue = bytes | std::views::drop(2) | std::views::stride(3);
    }

    std::string getMagicNumber()
    {
        return magic_number;
    }

    int getWidth()
    {
        return width;
    }

    int getHight()
    {
        return hight;
    }
};

int main()
{
    std::cout << "Please input the file location and press [ENTER]:\n";
    std::string file_location;
    std::getline(std::cin, file_location);
    ImageData image = ImageData(file_location);
    std::cout << "Magic Number: " << image.getMagicNumber() << std::endl;
    std::cout << "Width: " << image.getWidth() << std::endl;
    std::cout << "Hight: " << image.getHight() << std::endl;
    return 0;
}
